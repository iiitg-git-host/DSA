#include <stdio.h>
#include <stdlib.h>

typedef struct photo
{
    int identifier;

    int ratings[10];
    int rating_count;
    int primordial_rating;
    float average_rating;

    int max_heap_rating[6];
    int max_heap_size;

    int min_heap_rating[6];
    int min_heap_size;
} photo;

//              Utilities
void swap_photo(photo photos[], int first, int second);
void int_swap(int array[], int first, int second);
float average(int array[], int size);
int check_rating(int rating, int median);
int find_min_identifier(photo photos[], int size);
int find_max_identifier(photo photos[], int size);

//              photo functions
void add_photo(photo photos[], int *size);
photo new_photo(photo photos[], int size);
void add_rating(photo photos[], int size, int idx);
void delete_photo(photo photos[], int *size);

//              heap
void photo_max_heapify_up(photo photos[], int size, int idx);
void photo_max_heapify_down(photo photos[], int size, int idx);
void photo_build_max_heap(photo photos[], int size);

void rating_max_heapify_up(int array[], int size, int idx);
void rating_max_heapify_down(int array[], int size, int idx);
void rating_build_max_heap(int array[], int size);
void insert_max_heap(int max_heap[], int *max_heap_size, int key);
int get_max(int max_heap[]);
int extract_max(int max_heap[], int *max_heap_size);

void rating_min_heapify_up(int array[], int size, int idx);
void rating_min_heapify_down(int array[], int size, int idx);
void rating_build_min_heap(int array[], int size);
void insert_min_heap(int min_heap[], int *min_heap_size, int key);
int get_min(int min_heap[]);
int extract_min(int min_heap[], int *min_heap_size);
//              display
void print_photo(photo photo);
void print_all_photos(photo photos[], int size);
//              median
int get_median(int min_heap[], int min_heap_size, int max_heap[], int max_heap_size);
void stabilize_median(int min_heap[], int *min_heap_size, int max_heap[], int *max_heap_size, int median, int rate);

//              Utilities
void swap_photo(photo photos[], int first, int second)
{
    photo temp = photos[first];
    photos[first] = photos[second];
    photos[second] = temp;
}
void int_swap(int array[], int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
float average(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + array[i];
    }
    return sum / size;
}
int check_rating(int rating, int median)
{
    if (rating >= 0 && rating >= median - 3 && rating <= 20 && rating <= median + 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int find_identifier(photo photos[], int size, int identifier)
{
    for (int i = 0; i < size; i++)
    {
        if (photos[i].identifier == identifier)
        {
            return i;
        }
    }
    return -1;
}
int find_min_identifier(photo photos[], int size)
{
    int min = photos[0].identifier;
    int minIdx = -1;
    for (int i = 0; i < size; i++)
    {
        if (photos[i].identifier <= min)
        {
            min = photos[i].identifier;
            minIdx = i;
        }
    }
    return minIdx;
}
int find_max_identifier(photo photos[], int size)
{
    int max = photos[0].identifier;
    int maxIdx = -1;
    for (int i = 0; i < size; i++)
    {
        if (photos[i].identifier >= max)
        {
            max = photos[i].identifier;
            maxIdx = i;
        }
    }
    return maxIdx;
}

//              photo
void photo_max_heapify_up(photo photos[], int size, int idx)
{
    if (idx)
    {
        int parent;
        if (idx % 2 == 0)
        {
            parent = (idx - 2) / 2;
        }
        else
        {
            parent = (idx - 1) / 2;
        }
        if (photos[parent].average_rating < photos[idx].average_rating)
        {
            swap_photo(photos, idx, parent);
            photo_max_heapify_up(photos, size, parent);
        }
    }
}
void photo_max_heapify_down(photo photos[], int size, int idx)
{
    int maximum = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && photos[left].average_rating > photos[maximum].average_rating)
    {
        maximum = left;
    }
    if (right < size && photos[right].average_rating > photos[maximum].average_rating)
    {
        maximum = right;
    }
    if (maximum != idx)
    {
        swap_photo(photos, maximum, idx);
        photo_max_heapify_down(photos, size, maximum);
    }
}
void photo_build_max_heap(photo photos[], int size)
{
    int init = (size / 2) - 1;

    for (int i = init; i >= 0; i--)
    {
        photo_max_heapify_down(photos, size, i);
    }
}

photo new_photo(photo photos[], int size)
{
    photo new;
    int max_idx = find_max_identifier(photos, size);
    if (max_idx == -1)
    {
        new.identifier = 1;
    }
    else
    {
        new.identifier = photos[max_idx].identifier + 1;
    }
    new.rating_count = 0;
    new.average_rating = 0;
    new.min_heap_size = 0;
    new.max_heap_size = 0;
    return new;
}

void add_photo(photo photos[], int *size)
{
    if (*size == 1)
    {
        photos[*size] = new_photo(photos, *size);
        printf("Jury:\n");
        add_rating(photos, *size, *size);
        add_rating(photos, *size, *size);
        add_rating(photos, *size, *size);
        (*size)++;
        photo_build_max_heap(photos, *size);
    }
    else if (*size < 10)
    {
        photos[*size] = new_photo(photos, *size);
        printf("Jury:\n");
        add_rating(photos, *size, *size);
        add_rating(photos, *size, *size);
        add_rating(photos, *size, *size);
        (*size)++;
        photo_max_heapify_up(photos, *size, (*size) - 1);
    }
    else
    {
        int old = find_min_identifier(photos, *size);
        photos[old] = new_photo(photos, *size);
        printf("Jury:\n");
        add_rating(photos, *size, old);
        add_rating(photos, *size, old);
        add_rating(photos, *size, old);
        photo_max_heapify_up(photos, *size, old);
    }
}
void delete_photo(photo photos[], int *size)
{
    if (*size == 0)
    {
        printf("No photos in database\n");
    }
    else
    {
        int identifier;
        printf("Enter identifier of phototo be deleted(-1 to go back)\n");
        scanf("%d", &identifier);
        if (identifier != -1)
        {
            int idx = find_identifier(photos, *size, identifier);
            if (idx == -1)
            {
                printf("Identifier not found\n");
            }
            else
            {
                printf("Photo being deleted:\n");
                print_photo(photos[idx]);
                if (idx != (*size) - 1)
                {
                    swap_photo(photos, idx, (*size) - 1);
                }
                (*size)--;
                photo_max_heapify_down(photos, *size, 0);
            }
        }
    }
}

//            rating
void add_rating(photo photos[], int size, int idx)
{
    if (idx == -1)
    {
        printf("Identifier not found\n");
    }
    else
    {
        int rating;
        printf("Enter rating:\n");
        scanf("%d", &rating);
        int median = get_median(photos[idx].min_heap_rating, photos[idx].min_heap_size, photos[idx].max_heap_rating, photos[idx].max_heap_size);
        if (check_rating(rating, median) || photos[idx].rating_count == 0)
        {
            if (photos[idx].rating_count < 10)
            {
                photos[idx].ratings[photos[idx].rating_count++] = rating;
            }
            else
            {
                photos[idx].ratings[photos[idx].primordial_rating] = rating;
                photos[idx].primordial_rating = (photos[idx].primordial_rating + 1) % photos[idx].rating_count;
            }
            photos[idx].average_rating = average(photos[idx].ratings, photos[idx].rating_count);
            stabilize_median(photos[idx].min_heap_rating, &(photos[idx].min_heap_size), photos[idx].max_heap_rating, &(photos[idx].max_heap_size), median, rating);
        }
        else
        {
            printf("Invlid rating\n");
        }
    }
}

void rating_min_heapify_up(int array[], int size, int idx)
{
    if (idx)
    {
        int parent;
        if (idx % 2 == 0)
        {
            parent = (idx - 2) / 2;
        }
        else
        {
            parent = (idx - 1) / 2;
        }
        if (array[parent] > array[idx])
        {
            int_swap(array, idx, parent);
            rating_min_heapify_up(array, size, parent);
        }
    }
}
void rating_min_heapify_down(int array[], int size, int idx)
{

    int minimum = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left] < array[minimum])
    {
        minimum = left;
    }
    if (right < size && array[right] < array[minimum])
    {
        minimum = right;
    }
    if (minimum != idx)
    {
        int_swap(array, minimum, idx);
        rating_min_heapify_down(array, size, idx);
    }
}
void insert_min_heap(int min_heap[], int *min_heap_size, int key)
{
    min_heap[(*min_heap_size)++] = key;
    rating_min_heapify_up(min_heap, *min_heap_size, (*min_heap_size) - 1);
}
int get_min(int min_heap[])
{
    return min_heap[0];
}
int extract_min(int min_heap[], int *min_heap_size)
{
    if (*min_heap_size == 0)
    {
        return -1;
    }
    if (*min_heap_size == 1)
    {
        return min_heap[0];
    }
    int min = min_heap[0];
    min_heap[0] = min_heap[(*min_heap_size) - 1];
    rating_min_heapify_up(min_heap, (*min_heap_size) - 1, 0);
    return min;
}

void rating_max_heapify_up(int array[], int size, int idx)
{
    if (idx)
    {
        int parent;
        if (idx % 2 == 0)
        {
            parent = (idx - 2) / 2;
        }
        else
        {
            parent = (idx - 1) / 2;
        }
        if (array[parent] < array[idx])
        {
            int_swap(array, idx, parent);
            rating_max_heapify_up(array, size, parent);
        }
    }
}
void rating_max_heapify_down(int array[], int size, int idx)
{
    int maximum = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left] > array[maximum])
    {
        maximum = left;
    }
    if (right < size && array[right] > array[maximum])
    {
        maximum = right;
    }
    if (maximum != idx)
    {
        int_swap(array, maximum, idx);
        rating_max_heapify_down(array, size, idx);
    }
}
void insert_max_heap(int max_heap[], int *max_heap_size, int key)
{
    max_heap[(*max_heap_size)++] = key;
    rating_max_heapify_up(max_heap, *max_heap_size, (*max_heap_size) - 1);
}
int get_max(int max_heap[])
{
    return max_heap[0];
}
int extract_max(int max_heap[], int *max_heap_size)
{

    if (*max_heap_size == 0)
    {
        return -1;
    }
    if (*max_heap_size == 1)
    {
        return max_heap[0];
    }
    int max = max_heap[0];
    max_heap[0] = max_heap[(*max_heap_size) - 1];
    rating_max_heapify_down(max_heap, (*max_heap_size) - 1, 0);
    return max;
}

//          median
int get_median(int min_heap[], int min_heap_size, int max_heap[], int max_heap_size)
{
    if (max_heap_size == min_heap_size)
    {
        return (get_min(min_heap) + get_max(max_heap)) / 2;
    }
    else if (max_heap_size > min_heap_size)
    {
        return get_max(max_heap);
    }
    else if (max_heap_size < min_heap_size)
    {
        return get_min(min_heap);
    }
}
void stabilize_median(int min_heap[], int *min_heap_size, int max_heap[], int *max_heap_size, int median, int rate)
{
    if (*max_heap_size > *min_heap_size)
    {
        if (rate < median)
        {
            insert_min_heap(min_heap, min_heap_size, extract_max(max_heap, max_heap_size));
            insert_max_heap(max_heap, max_heap_size, rate);
        }
        else
        {
            insert_min_heap(min_heap, min_heap_size, rate);
        }
    }
    else if (*min_heap_size > *max_heap_size)
    {
        if (rate < median)
        {
            insert_max_heap(max_heap, max_heap_size, rate);
        }
        else
        {
            insert_max_heap(max_heap, max_heap_size, extract_min(min_heap, min_heap_size));
            insert_min_heap(min_heap, min_heap_size, rate);
        }
    }
    else
    {
        if (rate < median)
        {
            insert_max_heap(max_heap, max_heap_size, rate);
        }
        else
        {
            insert_min_heap(min_heap, min_heap_size, rate);
        }
    }
}

//                  Display
void print_photo(photo photo)
{
    int median = get_median(photo.min_heap_rating, photo.min_heap_size, photo.max_heap_rating, photo.max_heap_size);
    printf("\tIdentifier: %d,\t Average rating: %d,\t Median rating: %d,\t Ratings: [ ", photo.identifier, (int)photo.average_rating, median);
    for (int _ = 0; _ < photo.rating_count; _++)
    {
        printf("%d ", photo.ratings[_]);
    }
    printf("]\n");
}
void print_all_photos(photo photos[], int size)
{
    printf("Current Size : %d \n", size);
    for (int i = 0; i < size; i++)
    {
        print_photo(photos[i]);
    }
}

int main()
{
    photo photosdsliiitg[10];
    int photo_count = 0;
    while (1)
    {
        printf(" ####################################### \n");
        printf("/ 1.addPhoto\t\t\t\t\\\n\\ 2.addRating\t\t\t\t/\n/ 3.deletePhoto\t\t\t\t\\\n\\ 4.printAllPhotos\t\t\t/\n/ 5.printHighestRatedPhoto\t\t\t\\\n\\ 6.exit\t\t\t\t/\n");
        printf(" ####################################### \n");
        int ch;
        scanf("%d", &ch);
        if (ch == 1)
        {
            add_photo(photosdsliiitg, &photo_count);
        }
        else if (ch == 2)
        {
            int identifier;
            printf("Enter identifier of phototo rate\n");
            scanf("%d", &identifier);
            int idx = find_identifier(photosdsliiitg, photo_count, identifier);
            print_photo(photosdsliiitg[idx]);
            add_rating(photosdsliiitg, photo_count, find_identifier(photosdsliiitg, photo_count, identifier));
        }
        else if (ch == 3)
        {
            delete_photo(photosdsliiitg, &photo_count);
        }
        else if (ch == 4)
        {
            print_all_photos(photosdsliiitg, photo_count);
        }
        else if (ch == 5)
        {
            if (photo_count != 0)
            {
                print_photo(photosdsliiitg[0]);
            }
        }
        else if (ch == 6)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice\n");
        }
    }
}
