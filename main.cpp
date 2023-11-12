#include <iostream>

#include "blogpost.h"

int main()
{
    BlogPost bp;

    bp.edit("New text 1");
    bp.edit("New text 2");

    bp.publish();

    bp.edit("New text 3");
    bp.edit("New text 4");
    bp.edit("New text 5");
    bp.edit("New text 6");
    bp.edit("New text 7");

    bp.add_comment("Testcomment 1");
    bp.add_comment("Testcomment 2");
    bp.add_comment("Testcomment 3");
    bp.add_comment("Testcomment 4");
    bp.add_comment("Testcomment 5");

    std::cout << bp.get_text() << '\n';
    std::cout << bp.get_history().size() << '\n';

    std::flush(std::cout);
    return 0;
}