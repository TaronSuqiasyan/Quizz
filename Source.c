#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct QuizResult {
  char userName[50];
  int score;
  double timeTaken;
};

void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

void displayResults(struct QuizResult results[], int numResults) {
  printf("Results:\n");
  for (int i = 0; i < numResults; ++i) {
    printf("%s - Score: %d, Time: %.2f seconds\n", results[i].userName, results[i].score, results[i].timeTaken);
  }
}

void playQuiz(struct QuizResult* result) {
  const int numQuestions = 5;
  const char* questions[] = {
      "What is the capital of France?",
      "Who wrote 'Romeo and Juliet'?",
      "What is the chemical symbol for gold?",
      "In which year did the United States declare independence?",
      "What is the largest planet in our solar system?"
  };
  const char* options[][4] = {
      {"a) Paris", "b) Rome", "c) Berlin", "d) Madrid"},
      {"a) Charles Dickens", "b) William Shakespeare", "c) Jane Austen", "d) Mark Twain"},
      {"a) Au", "b) Ag", "c) Fe", "d) Cu"},
      {"a) 1776", "b) 1789", "c) 1800", "d) 1812"},
      {"a) Venus", "b) Mars", "c) Jupiter", "d) Saturn"}
  };
  const int correctOptions[] = { 1, 2, 1, 1, 3 };

  // Prompt for user's name
  printf("Enter your name: ");
  fgets(result->userName, sizeof(result->userName), stdin);
  result->userName[strcspn(result->userName, "\n")] = '\0'; // Remove newline character if present

  // Display and track time
  time_t startTime = time(NULL);
  result->score = 0;
  for (int i = 0; i < numQuestions; ++i) {
    // Clear the console screen
    system(CLEAR_SCREEN);

    // Display question and options
    printf("%s\n", questions[i]);
    for (int j = 0; j < 4; ++j) {
      printf("%s\n", options[i][j]);
    }

    int userAnswer;
    printf("Enter your answer (1-4): ");
    if (scanf_s("%d", &userAnswer) != 1) {
      printf("Invalid input. Exiting.\n");
      return;
    }

    clearInputBuffer(); // Clear the input buffer

    if (userAnswer >= 1 && userAnswer <= 4) {
      if (userAnswer == correctOptions[i]) {
        printf("Correct!\n");
        result->score++;
      }
      else {
        printf("Incorrect. Correct answer: %d\n", correctOptions[i]);
      }
    }
    else {
      printf("Invalid answer. Please enter a number between 1 and 4.\n");
      --i; // Repeat the current question
    }
  }
  time_t endTime = time(NULL);

  // Calculate and display the time taken
  result->timeTaken = difftime(endTime, startTime);
  printf("Quiz completed in %.2f seconds.\n", result->timeTaken);
}

int main() {
  int choice;
  const int maxResults = 10; // Adjust as needed
  struct QuizResult* results = malloc(maxResults * sizeof(struct QuizResult));
  int numResults = 0;

  if (results == NULL) {
    fprintf(stderr, "Memory allocation failed. Exiting.\n");
    return 1;
  }

  do {
    // Display menu options
    printf("Menu:\n");
    printf("1. Play Quiz\n");
    printf("2. View Results\n");
    printf("3. Exit\n");
    printf("Enter your choice (1-3): ");

    // Get user's choice
    if (scanf_s("%d", &choice) != 1) {
      printf("Invalid input. Exiting.\n");
      free(results); // Free allocated memory before exiting
      return 1;
    }

    clearInputBuffer(); // Clear the input buffer

    // Handle user's choice
    switch (choice) {
    case 1:
      // Code for playing the quiz
      if (numResults < maxResults) {
        playQuiz(&results[numResults]);
        numResults++;
      }
      else {
        printf("Maximum number of results reached. Unable to save result.\n");
      }
      break;
    case 2:
      // Code for viewing results
      displayResults(results, numResults);
      break;
    case 3:
      // Exit the program
      printf("Exiting. Goodbye!\n");
      break;
    default:
      // Invalid choice
      printf("Invalid choice. Please enter a number between 1 and 3.\n");
      break;
    }
  } while (choice != 3);

  free(results); // Free allocated memory before exiting

  return 0;
}