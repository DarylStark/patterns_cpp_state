#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "blogpost.h"
#include "blogpoststate.h"

class BlogPost;

/******************************************************************************/

BlogPostState::BlogPostState(BlogPost &context) : _context(context)
{
}

/******************************************************************************/

BlogPostDraftState::BlogPostDraftState(BlogPost &context) : BlogPostState(context)
{
}

void BlogPostDraftState::edit(std::string new_text)
{
    this->_context._text = new_text;
}

void BlogPostDraftState::publish()
{
    this->_context._published = true;
    this->_context.__transition(
        std::make_shared<BlogPostPublishedState>(this->_context));
}

void BlogPostDraftState::archive()
{
}

void BlogPostDraftState::unarchive()
{
}

void BlogPostDraftState::add_comment(std::string comment)
{
}

/******************************************************************************/

BlogPostPublishedState::BlogPostPublishedState(BlogPost &context) : BlogPostState(context)
{
}

void BlogPostPublishedState::edit(std::string new_text)
{
    this->_context._history.push_back(this->_context._text);
    this->_context._text = new_text;
}

void BlogPostPublishedState::publish()
{
}

void BlogPostPublishedState::archive()
{
}

void BlogPostPublishedState::unarchive()
{
}

void BlogPostPublishedState::add_comment(std::string comment)
{
}

/******************************************************************************/

BlogPostArchivedState::BlogPostArchivedState(BlogPost &context) : BlogPostState(context)
{
}

void BlogPostArchivedState::edit(std::string new_text)
{
}

void BlogPostArchivedState::publish()
{
}

void BlogPostArchivedState::archive()
{
}

void BlogPostArchivedState::unarchive()
{
}

void BlogPostArchivedState::add_comment(std::string comment)
{
}

/******************************************************************************/

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

/******************************************************************************/

int main()
{
    BlogPost bp;

    bp.edit("New text");

    bp.publish();

    bp.edit("New text");
    bp.edit("New text");
    bp.edit("New text");
    bp.edit("New text");
    bp.edit("New text");
    bp.edit("New text");

    std::cout << bp.get_text() << '\n';
    std::cout << bp.get_history().size() << '\n';

    std::flush(std::cout);
    return 0;
}