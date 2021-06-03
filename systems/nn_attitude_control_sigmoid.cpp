#include "../POLAR/Continuous.h"
#include "../NNTaylor.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
	intervalNumPrecision = 300;

	// Declaration of the state variables.
	unsigned int numVars = 9;

	// intput format (\omega_1, \psi_1, \omega_2, \psi_2, \omega_3, \psi_3)
	int x0_id = stateVars.declareVar("x0");
	int x1_id = stateVars.declareVar("x1");
	int x2_id = stateVars.declareVar("x2");
	int x3_id = stateVars.declareVar("x3");
	int x4_id = stateVars.declareVar("x4");
	int x5_id = stateVars.declareVar("x5");
	int u0_id = stateVars.declareVar("u0");
	int u1_id = stateVars.declareVar("u1");
	int u2_id = stateVars.declareVar("u2");

	int domainDim = numVars + 1;

	// Define the continuous dynamics.
	Expression_AST<Real> deriv_x0("u0/4 + x1*x2/4"); // theta_r = 0
	Expression_AST<Real> deriv_x1("u1/2 - 3*x0*x2/2");
	Expression_AST<Real> deriv_x2("u2 + 2*x0*x1");
	Expression_AST<Real> deriv_x3("x1*(x3^2/2 + x4^2/2 + x5^2/2 - x5/2) + x2*(x3^2/2 + x4^2/2 + x4/2 + x5^2/2) + x0*(x3^2/2 + x4^2/2 + x5^2/2 + 1/2)");
	Expression_AST<Real> deriv_x4("x0*(x3^2/2 + x4^2/2 + x5^2/2 + x5/2) + x2*(x3^2/2 - x3/2 + x4^2/2 + x5^2/2) + x1*(x3^2/2 + x4^2/2 + x5^2/2 + 1/2)");
	Expression_AST<Real> deriv_x5("x0*(x3^2/2 + x4^2/2 - x4/2 + x5^2/2) + x1*(x3^2/2 + x3/2 + x4^2/2 + x5^2/2) + x2*(x3^2/2 + x4^2/2 + x5^2/2 + 1/2)");
	Expression_AST<Real> deriv_u0("0");
	Expression_AST<Real> deriv_u1("0");
	Expression_AST<Real> deriv_u2("0");

	vector<Expression_AST<Real>> ode_rhs(numVars);
	ode_rhs[x0_id] = deriv_x0;
	ode_rhs[x1_id] = deriv_x1;
	ode_rhs[x2_id] = deriv_x2;
	ode_rhs[x3_id] = deriv_x3;
	ode_rhs[x4_id] = deriv_x4;
	ode_rhs[x5_id] = deriv_x5;
	ode_rhs[u0_id] = deriv_u0;
	ode_rhs[u1_id] = deriv_u1;
	ode_rhs[u2_id] = deriv_u2;

	Deterministic_Continuous_Dynamics dynamics(ode_rhs);

	// Specify the parameters for reachability computation.
	Computational_Setting setting;

	unsigned int order = stoi(argv[4]);

	// stepsize and order for reachability analysis
	setting.setFixedStepsize(0.005, order);

	// time horizon for a single control step
	setting.setTime(0.1);

	// cutoff threshold
	setting.setCutoffThreshold(1e-7);

	// queue size for the symbolic remainder
	setting.setQueueSize(2000);

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
	Interval init_x0(-0.445 - w, -0.445 + w), init_x1(-0.545 - w, -0.545 + w), init_x2(0.655 - w, 0.655 + w), init_x3(-0.745 - w, -0.745 + w), init_x4(0.855 - w, 0.855 + w), init_x5(-0.645 - w, -0.645 + w);
	// Interval init_x0(-0.25 - w, -0.25 + w), init_x1(-0.25 - w, -0.25 + w), init_x2(0.35 - w, 0.35 + w), init_x3(-0.35 - w, -0.35 + w), init_x4(0.45 - w, 0.45 + w), init_x5(-0.35 - w, -0.35 + w);
	Interval init_u0(0), init_u1(0), init_u2(0);
	std::vector<Interval> X0;
	X0.push_back(init_x0);
	X0.push_back(init_x1);
	X0.push_back(init_x2);
	X0.push_back(init_x3);
	X0.push_back(init_x4);
	X0.push_back(init_x5);
	X0.push_back(init_u0);
	X0.push_back(init_u1);
	X0.push_back(init_u2);

	// translate the initial set to a flowpipe
	Flowpipe initial_set(X0);

	// no unsafe set
	vector<Constraint> unsafeSet;

	// result of the reachability computation
	Result_of_Reachability result;

	// define the neural network controller
	string nn_name = "systems_with_networks/AttitudeControl/CLF_controller_layer_num_3_new";
	NeuralNetwork nn(nn_name);

	unsigned int maxOrder = 15;
	Global_Computation_Setting g_setting;
	g_setting.prepareForReachability(maxOrder);

	// the order in use
	// unsigned int order = 5;
	Interval cutoff_threshold(-1e-7, 1e-7);
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
	state_vars.push_back("x3");
	state_vars.push_back("x4");
	state_vars.push_back("x5");

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

		for (int i = 0; i < 6; i++)
		{
			tmv_input.tms.push_back(initial_set.tmvPre.tms[i]);
		}

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
		Matrix<Interval> rm1(nn.get_num_of_outputs(), 1);
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
			initial_set.tmvPre.tms[u0_id] = tmv_output.tms[0];
			initial_set.tmvPre.tms[u1_id] = tmv_output.tms[1];
			initial_set.tmvPre.tms[u2_id] = tmv_output.tms[2];
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
		}
		else
		{
			printf("Terminated due to too large overestimation.\n");
		}
	}

	vector<Interval> end_box;
	string reach_result;
	reach_result = "Verification result: Unknown(35)";
	result.fp_end_of_time.intEval(end_box, order, setting.tm_setting.cutoff_threshold);

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

	ofstream result_output("./outputs/nn_ac_sigmoid_" + to_string(if_symbo) + ".txt");
	if (result_output.is_open())
	{
		result_output << reach_result << endl;
		result_output << running_time << endl;
	}
	// you need to create a subdir named outputs
	// the file name is example.m and it is put in the subdir outputs
	plot_setting.plot_2D_octagon_MATLAB("nn_ac_sigmoid_x0_x1_" + to_string(if_symbo), result);

	plot_setting.setOutputDims(x2_id, x3_id);
	plot_setting.plot_2D_octagon_MATLAB("nn_ac_sigmoid_x2_x3_" + to_string(if_symbo), result);

	plot_setting.setOutputDims(x4_id, x5_id);
	plot_setting.plot_2D_octagon_MATLAB("nn_ac_sigmoid_x4_x5_" + to_string(if_symbo), result);

	return 0;
}
