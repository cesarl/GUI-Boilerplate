#ifndef					__SCORE_MANAGER_H__
# define				__SCORE_MANAGER_H__

#include				"GuiSelectableGroup.hh"
#include				"GuiSelectableText.hh"
#include				"GuiNumber.hh"
#include				"FontManager.hh"
#include				<fstream>
#include				<iostream>
#include				<sstream>
#include				<string>
#include				<cstring>
#include				<map>

typedef struct				s_score
{
  int					id;
  int					score;
  std::string				player;
  long					date;
}					Score;

class					ScoreManager
{
public:
  virtual ~ScoreManager();
  static ScoreManager			*getInstance();
  void					setPath(std::string const & path);
  bool					load();
  void					parseLine(std::string & line);
  bool					save();
  void					clear();
  void					erase(int id);
  void					registerScore(int score, std::string const & player);
  void					registerScore(Score *score);
  GuiSelectableGroup			*getGuiList();
private:
  int					id_;
  std::string				path_;
  GuiSelectableGroup			guiList_;
  std::multimap<int, Score*>		list_;
  std::ifstream				file_;
  std::ofstream				save_;
  typedef std::multimap<int, Score*>::iterator t_iter;
  ScoreManager();
};

#endif					// __SCORE_MANAGER_H__
