#ifndef __BLOGPOSTSTATE_H__
#define __BLOGPOSTSTATE_H__

#include <string>

class BlogPost;

class BlogPostStateException
{
public:
    BlogPostStateException(std::string error);
};

class BlogPostState
{
protected:
    BlogPost &_context;

public:
    // BlogPostState() {}
    BlogPostState(BlogPost &context);

    // Abstract methods
    virtual void edit(std::string new_text) = 0;
    virtual void publish() = 0;
    virtual void archive() = 0;
    virtual void unarchive() = 0;
    virtual void add_comment(std::string comment) = 0;
};

class BlogPostDraftState : public BlogPostState
{
public:
    BlogPostDraftState(BlogPost &context);

    void edit(std::string new_text);
    void publish();
    void archive();
    void unarchive();
    void add_comment(std::string comment);
};

class BlogPostPublishedState : public BlogPostState
{
public:
    BlogPostPublishedState(BlogPost &context);

    void edit(std::string new_text);
    void publish();
    void archive();
    void unarchive();
    void add_comment(std::string comment);
};

class BlogPostArchivedState : public BlogPostState
{
public:
    BlogPostArchivedState(BlogPost &context);

    void edit(std::string new_text);
    void publish();
    void archive();
    void unarchive();
    void add_comment(std::string comment);
};

#endif