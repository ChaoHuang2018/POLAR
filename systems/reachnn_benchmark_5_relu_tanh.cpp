#include "../POLAR/Continuous.h"
#include "../NNTaylor.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
	intervalNumPrecision = 600;

	// Declaration of the state variables.
	unsigned int numVars = 4;

	int x0_id = stateVars.declareVar("x0");
	int x1_id = stateVars.declareVar("x1");
	int x2_id = stateVars.declareVar("x2");
	int u_id = stateVars.declareVar("u");

	int domainDim = numVars + 1;

	// Define the continuous dynamics.
	Expression_AST<Real> deriv_x0("x2^3-x1"); // theta_r = 0
	Expression_AST<Real> deriv_x1("x2");
	Expression_AST<Real> deriv_x2("u");
	Expression_AST<Real> deriv_u("0");

	vector<Expression_AST<Real>> ode_rhs(numVars);
	ode_rhs[x0_id] = deriv_x0;
	ode_rhs[x1_id] = deriv_x1;
	ode_rhs[x2_id] = deriv_x2;
	ode_rhs[u_id] = deriv_u;

	Deterministic_Continuous_Dynamics dynamics(ode_rhs);

	// Specify the parameters for reachability computation.
	Computational_Setting setting;

	unsigned int order = stoi(argv[4]);

	// stepsize and order for reachability analysis
	setting.setFixedStepsize(0.005, order);

	// time horizon for a single control step
	setting.setTime(0.2);

	// cutoff threshold
	setting.setCutoffThreshold(1e-10);

	// queue size for the symbolic remainder
	setting.setQueueSize(1000);

	// print out the steps
	setting.printOff();

	// remainder estimation
	Interval I(-0.01, 0.01);
	vector<Interval> remainder_estimation(numVars, I);
	setting.setRemainderEstimation(remainder_estimation);

	//setting.printOn();

	setting.prepare();

	/*
	 * Initial set can be a box which is represented by a vector of intervals.
	 * The i-th component denotes the initial set of the i-th state variable.
	 */
	double w = stod(argv[1]);
	int steps = stoi(argv[2]);
	Interval init_x0(0.39 - w, 0.39 + w), init_x1(0.46 - w, 0.46 + w), init_x2(0.26 - w, 0.26 + w), init_u(0); //w=0.01
	std::vector<Interval> X0;
	X0.push_back(init_x0);
	X0.push_back(init_x1);
	X0.push_back(init_x2);
	X0.push_back(init_u);

	// translate the initial set to a flowpipe
	Flowpipe initial_set(X0);

	// no unsafe set
	vector<Constraint> unsafeSet;

	// result of the reachability computation
	Result_of_Reachability result;

	// define the neural network controller
	string nn_name = "systems_with_networks/reachnn_benchmark_5/nn_5_relu_tanh";
	NeuralNetwork nn(nn_name);

	unsigned int maxOrder = 15;
	Global_Computation_Setting g_setting;
	g_setting.prepareForReachability(maxOrder);

	// the order in use
	// unsigned int order = 5;
	Interval cutoff_threshold(-1e-10, 1e-10);
	unsigned int bernstein_order = stoi(argv[3]);
	unsigned int partition_num = 4000;

	unsigned int if_symbo = stoi(argv[5]);

	double err_max = 0;
	time_t start_timer;
	time_t end_timer;
	double seconds;
	time(&start_timer);

	vector<string> state_vars;
	state_vars.push_back("x0");
	state_vars.push_back("x1");
	state_vars.push_back("x2");

	if (if_symbo == 0)
	{
		cout << "High order abstraction starts." << endl;
	}
	else
	{
		cout << "High order abstraction with symbolic remainder starts." << endl;
	}

	// perform 35 control steps
	for (int iter = 0; iter < steps; ++iter)
	{
		cout << "Step " << iter << " starts.      " << endl;
		//vector<Interval> box;
		//initial_set.intEval(box, order, setting.tm_setting.cutoff_threshold);
		TaylorModelVec<Real> tmv_input;

		// tmv_input.tms.push_back(initial_set.tmvPre.tms[0]);
		// tmv_input.tms.push_back(initial_set.tmvPre.tms[1]);

		TaylorModelVec<Real> tmv_temp;
		initial_set.compose(tmv_temp, order, cutoff_threshold);
		tmv_input.tms.push_back(tmv_temp.tms[0]);
		tmv_input.tms.push_back(tmv_temp.tms[1]);
		tmv_input.tms.push_back(tmv_temp.tms[2]);

		// taylor propagation
		NNTaylor nn_taylor(nn);
		TaylorInfo ti(g_setting, order, bernstein_order, partition_num, cutoff_threshold);
		TaylorModelVec<Real> tmv_output;
		if (if_symbo == 0)
		{
			nn_taylor.get_output_tmv(tmv_output, tmv_input, ti, initial_set.domain);
		}
		else
		{
			nn_taylor.NN_Reach(tmv_output, tmv_input, ti, initial_set.domain);
		}
		// cout << "initial_set.domain: " << initial_set.domain[0] << initial_set.domain[1] << endl;
		Matrix<Interval> rm1(1, 1);
		tmv_output.Remainder(rm1);
		cout << "Neural network taylor remainder: " << rm1 << endl;

		// taylor
		// NNTaylor nn_taylor1(nn);
		// vector<Interval> box;
		// initial_set.intEval(box, order, setting.tm_setting.cutoff_threshold);
		// cout << "initial_set: " << box[0] << box[1] << endl;
		// vector<Interval> box_state;
		// for (int i = 0; i < state_vars.size(); i++)
		// {
		// 	box_state.push_back(box[i]);
		// }
		// nn_taylor1.set_taylor_linear(state_vars, box_state);
		// cout << "11111" << endl;
		// vector<double> jcb = nn_taylor1.get_jacobian();
		// vector<Real> jcb_real;
		// for (int i = 0; i < jcb.size(); i++)
		// {
		// 	jcb_real.push_back(Real(jcb[i]));
		// }
		// Interval rem = nn_taylor1.get_taylor_remainder() + nn_taylor1.get_output();
		// cout << "Whole remainder: " << rem << endl;
		// Polynomial<Real> tm_coef(jcb_real);
		// TaylorModel<Real> tm_output2(jcb_real, rem);

		// if (rm1[0][0].width() < rem.width())
		if (true)
		{
			tmv_temp.tms[u_id] = tmv_output.tms[0];
			Flowpipe flow_temp(tmv_temp, initial_set.domain, cutoff_threshold);
			initial_set = flow_temp;

			// initial_set.tmvPre.tms[u_id] = tmv_output.tms[0];

			cout << "TM -- Propagation" << endl;
		}
		else
		{
			// initial_set.tmvPre.tms[u_id] = tm_output2;
			// cout << "TM -- Linear, whole" << endl;
		}

		dynamics.reach(result, setting, initial_set, unsafeSet);

		if (result.status == COMPLETED_SAFE || result.status == COMPLETED_UNSAFE || result.status == COMPLETED_UNKNOWN)
		{
			initial_set = result.fp_end_of_time;
			cout << "Flowpipe taylor remainder: " << initial_set.tmv.tms[0].remainder << "     " << initial_set.tmv.tms[1].remainder << endl;
		}
		else
		{
			printf("Terminated due to too large overestimation.\n");
			return 1;
		}
	}

	vector<Interval> end_box;
	string reach_result;
	reach_result = "Verification result: Unknown(35)";
	result.fp_end_of_time.intEval(end_box, order, setting.tm_setting.cutoff_threshold);

	if (end_box[0].inf() >= 0.0 && end_box[0].sup() <= 0.2 && end_box[1].inf() >= 0.05 && end_box[1].sup() <= 0.3)
	{
		reach_result = "Verification result: Yes(35)";
	}

	if (end_box[0].inf() >= 0.2 || end_box[0].sup() <= 0.0 || end_box[1].inf() >= 0.3 || end_box[1].sup() <= 0.05)
	{
		reach_result = "Verification result: No(35)";
	}

	time(&end_timer);
	seconds = difftime(start_timer, end_timer);

	// plot the flowpipes in the x-y plane
	result.transformToTaylorModels(setting);

	Plot_Setting plot_setting;
	plot_setting.setOutputDims(x0_id, x1_id);

	int mkres = mkdir("./outputs", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	if (mkres < 0 && errno != EEXIST)
	{
		printf("Can not create the directory for images.\n");
		exit(1);
	}

	std::string running_time = "Running Time: " + to_string(-seconds) + " seconds";

	ofstream result_output("./outputs/reachnn_benchmark_5_relu_tanh_" + to_string(if_symbo) + ".txt");
	if (result_output.is_open())
	{
		result_output << reach_result << endl;
		result_output << running_time << endl;
	}
	// you need to create a subdir named outputs
	// the file name is example.m and it is put in the subdir outputs
	plot_setting.plot_2D_octagon_MATLAB("reachnn_benchmark_5_relu_tanh_" + to_string(if_symbo), result);

	return 0;
}
