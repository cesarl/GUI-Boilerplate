#ifndef					__OPTION_MANAGER_HH__
# define				__OPTION_MANAGER_HH__

#include				<string>
#include				<map>
#include				<iostream> // for debug
#include				"OptionValue.hpp"

class					OptionManager
{
public:
  ~OptionManager()
  {}
  static OptionManager			*getInstance()
  {
    static OptionManager		that;
    return &that;
  }

  template				<typename T>
  void					create(std::string key, T const & value)
  {
    Option				*tmp;

    tmp = new OptionValue<T>(key, value);
    this->list_.insert(t_pair(key, tmp));
  }

  template				<typename T>
  OptionValue<T>			*getOption(std::string key)
  {
    t_iter				it;
    OptionValue<T>			*value;

    it = this->list_.find(key);
    if (it != this->list_.end())
      {
	value = dynamic_cast<OptionValue<T>*>(it->second);
	return value;
      }
    return NULL;
  }

  Option				*getOption(std::string key)
  {
    t_iter				it;

    it = this->list_.find(key);
    if (it != this->list_.end())
      {
	return it->second;
      }
    return NULL;
  }

  template				<typename T>
  void					setOption(std::string key, const T & value)
  {
    std::cout << key << " " << value << std::endl;
    t_iter				it;

    it = this->list_.find(key);
    if (it != this->list_.end())
      dynamic_cast<OptionValue<T>*>(it->second)->setValue(value);
    else
      this->create<T>(key, value);
  }

private:
  std::map<std::string, Option*>			list_;
  typedef std::map<std::string, Option*>::iterator	t_iter;
  typedef std::pair<std::string, Option*>		t_pair;
    OptionManager()
  {}
};

#endif					// __OPTION_MANAGER_HH__
