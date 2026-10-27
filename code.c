#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char name[50];
    char artist[50];
    struct Song *prev;
    struct Song *next;
};

struct Song *head = NULL;
struct Song *current = NULL;

// Add a song
void addSong() {
    struct Song *newSong;
    
    newSong = (struct Song *)malloc(sizeof(struct Song));

    printf("Enter song name: ");
    scanf(" %[^\n]", newSong->name);

    printf("Enter artist name: ");
    scanf(" %[^\n]", newSong->artist);

    newSong->prev = NULL;
    newSong->next = NULL;

    if (head == NULL) {
        head = newSong;
        current = newSong;
    } else {
        struct Song *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newSong;
        newSong->prev = temp;
    }

    printf("Song added successfully!\n");
}

// Display playlist
void displayPlaylist() {
    struct Song *temp = head;

    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\n----- MUSIC PLAYLIST -----\n");

    while (temp != NULL) {
        printf("Song: %s | Artist: %s\n",
               temp->name, temp->artist);
        temp = temp->next;
    }
}

// Search a song
void searchSong() {
    char search[50];
    struct Song *temp = head;

    printf("Enter song name to search: ");
    scanf(" %[^\n]", search);

    while (temp != NULL) {
        if (strcmp(temp->name, search) == 0) {
            printf("Song Found!\n");
            printf("Song: %s\n", temp->name);
            printf("Artist: %s\n", temp->artist);
            return;
        }

        temp = temp->next;
    }

    printf("Song not found.\n");
}

// Delete a song
void deleteSong() {
    char name[50];
    struct Song *temp = head;

    printf("Enter song name to delete: ");
    scanf(" %[^\n]", name);

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {

            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            if (current == temp) {
                current = (temp->next != NULL)
                         ? temp->next
                         : temp->prev;
            }

            free(temp);

            printf("Song deleted successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Song not found.\n");
}

// Play current song
void playCurrent() {
    if (current == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\nNow Playing: %s - %s\n",
           current->name, current->artist);
}

// Play next song
void nextSong() {
    if (current == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    if (current->next != NULL) {
        current = current->next;
        playCurrent();
    } else {
        printf("This is the last song.\n");
    }
}

// Play previous song
void previousSong() {
    if (current == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    if (current->prev != NULL) {
        current = current->prev;
        playCurrent();
    } else {
        printf("This is the first song.\n");
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\n========== MUSIC PLAYLIST MANAGER ==========\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Display Playlist\n");
        printf("4. Search Song\n");
        printf("5. Play Current Song\n");
        printf("6. Next Song\n");
        printf("7. Previous Song\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addSong();
                break;

            case 2:
                deleteSong();
                break;

            case 3:
                displayPlaylist();
                break;

            case 4:
                searchSong();
                break;

            case 5:
                playCurrent();
                break;

            case 6:
                nextSong();
                break;

            case 7:
                previousSong();
                break;

            case 8:
                printf("Thank you for using Music Playlist Manager!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 8);

    return 0;
}
