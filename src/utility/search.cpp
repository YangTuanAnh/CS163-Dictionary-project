#include "search.h"
#include "Dictionary.h"

const std::string digits = "0123456789";
const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
const std::string space = " ";

Dictionary slang("../data/slang", uppercase + digits + symbols + space);
//Dictionary engeng("../data/engeng", lowercase + digits + space + "-\'.");

//Dictionary slang("../data/engeng", lowercase + digits + space + "-\'.");