#include				"Option.hh"

Option::Option(const std::string & key) :
  key_(key)
{}

Option::~Option()
{}

const std::string			&Option::getKey() const
{
  return this->key_;
}
