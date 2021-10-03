/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MODELPARSER_TAB_H_INCLUDED
# define YY_YY_MODELPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    IDENT = 259,                   /* IDENT  */
    STATEVAR = 260,                /* STATEVAR  */
    TMVAR = 261,                   /* TMVAR  */
    TM = 262,                      /* TM  */
    EQ = 263,                      /* EQ  */
    GEQ = 264,                     /* GEQ  */
    LEQ = 265,                     /* LEQ  */
    ASSIGN = 266,                  /* ASSIGN  */
    END = 267,                     /* END  */
    MODE = 268,                    /* MODE  */
    INIT = 269,                    /* INIT  */
    BELONGSTO = 270,               /* BELONGSTO  */
    PARAAGGREG = 271,              /* PARAAGGREG  */
    INTAGGREG = 272,               /* INTAGGREG  */
    TMAGGREG = 273,                /* TMAGGREG  */
    OUTPUT = 274,                  /* OUTPUT  */
    NOOUTPUT = 275,                /* NOOUTPUT  */
    CONTINUOUS = 276,              /* CONTINUOUS  */
    HYBRID = 277,                  /* HYBRID  */
    SETTING = 278,                 /* SETTING  */
    FIXEDST = 279,                 /* FIXEDST  */
    FIXEDORD = 280,                /* FIXEDORD  */
    ADAPTIVEST = 281,              /* ADAPTIVEST  */
    ADAPTIVEORD = 282,             /* ADAPTIVEORD  */
    ORDER = 283,                   /* ORDER  */
    MIN = 284,                     /* MIN  */
    MAX = 285,                     /* MAX  */
    REMEST = 286,                  /* REMEST  */
    INTERVAL = 287,                /* INTERVAL  */
    OCTAGON = 288,                 /* OCTAGON  */
    GRID = 289,                    /* GRID  */
    PLOT = 290,                    /* PLOT  */
    QRPRECOND = 291,               /* QRPRECOND  */
    IDPRECOND = 292,               /* IDPRECOND  */
    TIME = 293,                    /* TIME  */
    MODES = 294,                   /* MODES  */
    JUMPS = 295,                   /* JUMPS  */
    INV = 296,                     /* INV  */
    GUARD = 297,                   /* GUARD  */
    RESET = 298,                   /* RESET  */
    START = 299,                   /* START  */
    MAXJMPS = 300,                 /* MAXJMPS  */
    PRINTON = 301,                 /* PRINTON  */
    PRINTOFF = 302,                /* PRINTOFF  */
    UNSAFESET = 303,               /* UNSAFESET  */
    CONTINUOUSFLOW = 304,          /* CONTINUOUSFLOW  */
    HYBRIDFLOW = 305,              /* HYBRIDFLOW  */
    TAYLOR_PICARD = 306,           /* TAYLOR_PICARD  */
    TAYLOR_REMAINDER = 307,        /* TAYLOR_REMAINDER  */
    TAYLOR_POLYNOMIAL = 308,       /* TAYLOR_POLYNOMIAL  */
    EXP = 309,                     /* EXP  */
    SIN = 310,                     /* SIN  */
    COS = 311,                     /* COS  */
    LOG = 312,                     /* LOG  */
    SQRT = 313,                    /* SQRT  */
    ODE = 314,                     /* ODE  */
    CUTOFF = 315,                  /* CUTOFF  */
    PRECISION = 316,               /* PRECISION  */
    GNUPLOT = 317,                 /* GNUPLOT  */
    MATLAB = 318,                  /* MATLAB  */
    COMPUTATIONPATHS = 319,        /* COMPUTATIONPATHS  */
    LTIODE = 320,                  /* LTIODE  */
    LTVODE = 321,                  /* LTVODE  */
    PAR = 322,                     /* PAR  */
    UNC = 323,                     /* UNC  */
    UNIVARIATE_POLYNOMIAL = 324,   /* UNIVARIATE_POLYNOMIAL  */
    MULTIVARIATE_POLYNOMIAL = 325, /* MULTIVARIATE_POLYNOMIAL  */
    TIME_INV = 326,                /* TIME_INV  */
    TIME_VAR = 327,                /* TIME_VAR  */
    STEP = 328,                    /* STEP  */
    TRUE = 329,                    /* TRUE  */
    FALSE = 330,                   /* FALSE  */
    LINEARCONTINUOUSFLOW = 331,    /* LINEARCONTINUOUSFLOW  */
    EXPRESSION = 332,              /* EXPRESSION  */
    MATRIX = 333,                  /* MATRIX  */
    uminus = 334                   /* uminus  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "modelParser.y"

	double															dblVal;
	int																intVal;
	std::string														*identifier;
	std::vector<flowstar::Interval>									*intVec;
	std::vector<std::vector<flowstar::Interval> >					*intsVec;
	flowstar::Polynomial<flowstar::Interval>						*intPoly;
	flowstar::Polynomial<flowstar::Real>							*realPoly;
	flowstar::UnivariatePolynomial<flowstar::Real>					*uniPoly;
	std::vector<flowstar::Polynomial<flowstar::Interval> >			*intPolyVec;
	std::vector<flowstar::UnivariatePolynomial<flowstar::Real> >	*uniPolyVec;
	std::vector<flowstar::Flowpipe>									*flowpipeVec;
	std::vector<flowstar::Constraint>								*constraintVec;
	flowstar::TaylorModelVec<flowstar::Real>						*taylorModelVec;
	flowstar::Expression_AST<flowstar::Interval>					*pIntExpression;
	std::vector<flowstar::Expression_AST<flowstar::Interval> >		*intExpressionVec;
	LTI_Term														*pLTITerm;
	LTI_ODE_description												*pLTIDescription;
	LTV_Term														*pLTVTerm;
	LTV_ODE_description												*pLTVDescription;

#line 165 "modelParser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MODELPARSER_TAB_H_INCLUDED  */
