#include <memory>
#include "blogpost.h"

BlogPost::BlogPost()
    : _state(std::make_shared<BlogPostDraftState>(*this)),
      _published(false), _archived(false)
{
}

void BlogPost::__transition(std::shared_ptr<BlogPostState> state)
{
    _state = state;
}

void BlogPost::edit(std::string new_text)
{
    // Delegate this action to the state object
    _state->edit(new_text);
}
void BlogPost::publish()
{
    // Delegate this action to the state object
    _state->publish();
}
void BlogPost::archive()
{
    // Delegate this action to the state object
    _state->archive();
}
void BlogPost::unarchive()
{
    // Delegate this action to the state object
    _state->unarchive();
}
void BlogPost::add_comment(std::string comment)
{
    // Delegate this action to the state object
    _state->add_comment(comment);
}

const std::string &BlogPost::get_text() const
{
    return _text;
}

const std::vector<std::string> &BlogPost::get_history() const
{
    return _history;
}

const bool BlogPost::is_published() const
{
    return _published;
}