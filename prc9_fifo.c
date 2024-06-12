#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int front = 0, rear = 0, page_faults = 0;

    // Initialize the frame array with -1 to indicate empty slots
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    // Iterate over each page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in any of the frames
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found in the frame
        if (!found) {
            // Replace the oldest page (FIFO logic)
            frame[rear] = page;
            rear = (rear + 1) % capacity;
            page_faults++;
        }

        // Display the frame status
        printf("Frame status after inserting page %d: ", page);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1) {
                printf(" -");
            } else {
                printf(" %d", frame[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", page_faults);
}

int main() {
    int n, capacity;

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];

    // Input page reference string
    printf("Enter the page reference string: \n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    // Input capacity of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Call FIFO page replacement function
    fifoPageReplacement(pages, n, capacity);

    return 0;
}
