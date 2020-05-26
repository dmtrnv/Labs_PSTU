#include "SearchTree.h"


int main(int argc, char *argv[])
{
	try
	{
		SearchTree st;
		st.drawTree(argc, argv, 800, 600, 10, 2);
	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}