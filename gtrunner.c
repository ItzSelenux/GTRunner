#include "gtrunner.h"

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--cfg") == 0)
		{
			cfg = 1;
		}
	}

	gtk_init(&argc, &argv);
	create_window();
}
