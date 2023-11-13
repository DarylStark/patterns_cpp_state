#include <iostream>
#include <memory>
#include "blogpost.h"
#include "blogpoststate.h"

BlogPostStateException::BlogPostStateException(std::string error)
{
    std::cerr << "ERROR: " << error << std::endl;
}

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
    throw BlogPostStateException("Cannot archive a post that is still in draft");
}

void BlogPostDraftState::unarchive()
{
    throw BlogPostStateException("Cannot unarchive a post that is still in draft");
}

void BlogPostDraftState::add_comment(std::string comment)
{
    throw BlogPostStateException("Cannot add comments to a post in draft");
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
    throw BlogPostStateException("Post is already published");
}

void BlogPostPublishedState::archive()
{
    this->_context._archived = true;
    this->_context.__transition(
        std::make_shared<BlogPostArchivedState>(this->_context));
}

void BlogPostPublishedState::unarchive()
{
    throw BlogPostStateException("Cannot unarchive a post that is not archived");
}

void BlogPostPublishedState::add_comment(std::string comment)
{
    this->_context._comments.push_back(comment);
}

/******************************************************************************/

BlogPostArchivedState::BlogPostArchivedState(BlogPost &context) : BlogPostState(context)
{
}

void BlogPostArchivedState::edit(std::string new_text)
{
    throw BlogPostStateException("Cannot edit a post that is archived");
}

void BlogPostArchivedState::publish()
{
    throw BlogPostStateException("Cannot publish a post that is archived");
}

void BlogPostArchivedState::archive()
{
    throw BlogPostStateException("Post is already archived");
}

void BlogPostArchivedState::unarchive()
{
    this->_context._archived = true;
    this->_context.__transition(
        std::make_shared<BlogPostPublishedState>(this->_context));
}

void BlogPostArchivedState::add_comment(std::string comment)
{
    throw BlogPostStateException("Cannot add comments to a archived post");
}
