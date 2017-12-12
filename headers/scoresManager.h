#ifndef SCORES
#define SCORES

#define NBSCORE 10

typedef struct __scoreList ScoreList;
struct __scoreList {
  int nbScores;
  int scoresValues[NBSCORE];
};

ScoreList readScoreList(ScoreList scores);
int checkNewScore(ScoreList scores, int newScore);
int writeNewScores(ScoreList scores, int newScore, int scoreCheckValue);
int fileOpenerW(FILE** file, char* fileName);

#endif
