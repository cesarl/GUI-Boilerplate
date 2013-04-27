#ifndef					__OPTION_H__
# define				__OPTION_H__

#include				<string>

class					Option
{
public:
  Option(const std::string & key);
  virtual ~Option();
  const std::string			&getKey() const;
protected:
  std::string				key_;
};

#endif					// __OPTION_H__
