#include "search.h"
#include "Dictionary.h"

//Dictionary slang("CS163_github/data/slang", uppercase + symbols + digits + space);

//Dictionary engeng("CS163_github/data/engeng", lowercase + digits + space + "-\'.");
//Dictionary slang("CS163_github/data/engeng",lowercase + digits + space + "-\'.", lowercase + digits);
Dictionary data[4] =
{
	{"CS163_github/data/engeng", lowercase + digits + space + "-\'.", lowercase + digits},
	{"CS163_github/data/engvie", lowercase + digits + space + "-\'.", lowercase + digits},
	{"CS163_github/data/slang", uppercase + digits + symbols + space, lowercase + digits},
	{"CS163_github/data/emotional", uppercase + digits + symbols + space, lowercase + digits}
};