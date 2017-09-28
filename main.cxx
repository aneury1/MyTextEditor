#include "DeveloperWorkbench.hxx"
#include <Fl/FL.H>


int main(int argc, char *argv[])
{
	int w, h;
	w = Fl::w() - 10;
	h = Fl::h() - 30;

	DeveloperWorkbench *workbench = DeveloperWorkbench::get(w,h);

	workbench->end();

	workbench->show(argc, argv);

	Fl::run();
	delete workbench;

	return 0;
}
