#ifndef __BLOGPOST_H__
#define __BLOGPOST_H__

#include <string>
#include <memory>
#include <vector>

#include "blogpoststate.h"

class BlogPost
{
    friend class BlogPostState;
    friend class BlogPostDraftState;
    friend class BlogPostPublishedState;
    friend class BlogPostArchivedState;

protected:
    std::shared_ptr<BlogPostState> _state;
    std::vector<std::string> _history;
    std::vector<std::string> _comments;
    std::string _text;
    bool _published;
    bool _archived;

private:
    void __transition(std::shared_ptr<BlogPostState> state);

public:
    BlogPost();

    // Behaviour
    void edit(std::string new_text);
    void publish();
    void archive();
    void unarchive();
    void add_comment(std::string comment);

    // Getters
    const std::string &get_text() const;
    const std::vector<std::string> &get_history() const;
    const bool is_published() const;
};

#endif