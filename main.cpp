#include <iostream>
#include <exception>
/* Autor: Ognjen Jarčević Datum: 11.06.2022. */

//#include "SyntaxAnalysis.h"
//#include "LivenessAnalysis.h"
#include "ResourceAllocation.h"
using namespace std;

int main()
{
	try
	{
		//std::string fileName = "examples\\simple.mavn";
		std::string fileName = ".\\..\\examples\\multiply.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}


		SyntaxAnalysis syntax(lex);

		if (syntax.Do())
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			cout << "Syntax analysis failed!" << endl;
		}

		syntax.printVarList();
		syntax.printAll();

		livenessAnalysis();

		InterferenceGraph ig;//interferenceGraph
		stack<Variable*> ss;//simplificationStack

		ig.fillInterferenceGraph();
		ig.print();
		bool nijeSpill = simplify(ig,ss);
		if (nijeSpill)
		{
			ig.print();
			doResourceAllocation(ig, ss);
			syntax.printAll();
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
