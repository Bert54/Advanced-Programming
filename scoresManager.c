#include <stdio.h>
#include <stdlib.h>
#include "headers/scoresManager.h"
#include "headers/entryReader.h"

ScoreList readScoreList(ScoreList scores) {
  FILE* scoreFile = NULL;
  int i = 0;
  char* filePath = "content/txt/scores.txt";
  if (fileOpener(&scoreFile, filePath) == 1) {
    scores.nbScores = NBSCORE;
    while (i < NBSCORE && fscanf(scoreFile,"%d", &(scores.scoresValues[i])) != EOF) {
      i++;
    }
    while (i < NBSCORE) {
      scores.scoresValues[i] = 0;
      i++;
    }
    fileCloser(&scoreFile);
  }
  else {
    scores.nbScores = -1;
  }
  return scores;
}

int checkNewScore(ScoreList scores, int newScore) {
  int i = 0, posNewGoodScore, newGoodScore = 0;
  if (scores.nbScores > 0) {
    while (i < scores.nbScores && !newGoodScore) {
      if (newScore > scores.scoresValues[i]) {
	posNewGoodScore = i;
	newGoodScore = 1;
      }
      i++;
    }
  }
  else {
    return -1;
  }
  if (posNewGoodScore < scores.nbScores) {
    return posNewGoodScore;
  }
  return scores.nbScores;
}

int writeNewScores(ScoreList scores, int newScore, int scoreCheckValue) {
  FILE* scoreFile = NULL;
  int i = 0;
  char* filePath = "content/txt/scores.txt";
  int curScoreFile, tempScore;
  if (scoreCheckValue >= 0 && scoreCheckValue < scores.nbScores) {
    if (fileOpenerW(&scoreFile, filePath) == 1) {
      while (i < scoreCheckValue) {
	i++;
      }
      tempScore = scores.scoresValues[i];
      scores.scoresValues[i] = newScore;
      i++;
      while (i < scores.nbScores) {
	curScoreFile = tempScore;
	tempScore = scores.scoresValues[i];
	scores.scoresValues[i] = curScoreFile;
	i++;
      }
      i = 0;
      while (i < scores.nbScores) {
	fprintf(scoreFile, "%d\n", scores.scoresValues[i]);
	i++;
      }
      fileCloser(&scoreFile);
    }
    else {
      return -1;
    }
  }
  return 0;
}

int fileOpenerW(FILE** file, char* fileName) {
  *file = fopen(fileName,"r+");
  if (*file == NULL) {
    printf("Error: cannot open file.\n");
    return -1;
  }
  return 1;
}
