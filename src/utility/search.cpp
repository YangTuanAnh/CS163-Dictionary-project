#include "search.h"
#include "Dictionary.h"

//Dictionary slang("CS163_github/data/slang", uppercase + symbols + digits + space);

//Dictionary engeng("CS163_github/data/engeng", lowercase + digits + space + "-\'.");
//Dictionary slang("CS163_github/data/engeng",lowercase + digits + space + "-\'.", lowercase + digits);
Dictionary data[4] =
{
	{"../data/engeng", lowercase + digits + space + "-\'.", lowercase + digits},
	{"../data/engvie", lowercase + digits + space + "-\'.", lowercase + digits},
	{"../data/slang", uppercase + digits + symbols + space, lowercase + digits},
	{"../data/emotional", uppercase + digits + symbols + space, lowercase + digits}
};