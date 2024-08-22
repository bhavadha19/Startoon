#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double calculate_mean(double data[], int size) {
    double sum = 0.0;
    for(int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

double calculate_median(double data[], int size) {
    // Sort the array
    for(int i = 0; i < size-1; i++) {
        for(int j = i+1; j < size; j++) {
            if(data[i] > data[j]) {
                double temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    if(size % 2 == 0) {
        return (data[size/2 - 1] + data[size/2]) / 2;
    } else {
        return data[size/2];
    }
}

double calculate_std_dev(double data[], int size) {
    double mean = calculate_mean(data, size);
    double sum = 0.0;
    for(int i = 0; i < size; i++) {
        sum += pow(data[i] - mean, 2);
    }
    return sqrt(sum / size);
}

double calculate_range(double data[], int size) {
    double min = data[0], max = data[0];
    for(int i = 1; i < size; i++) {
        if(data[i] < min) min = data[i];
        if(data[i] > max) max = data[i];
    }
    return max - min;
}
int read_csv(const char* filename, double data[], int max_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%lf,", &data[i]) != EOF && i < max_size) {
        i++;
    }
    fclose(file);
    return i; // Return the number of data points read
}

int main() {
    const int MAX_SIZE = 1000;
    double dataset1[MAX_SIZE];
    double dataset2[MAX_SIZE];

    int size1 = read_csv("Data_1.csv", dataset1, MAX_SIZE);
    int size2 = read_csv("Data_2.csv", dataset2, MAX_SIZE);

    if (size1 == 0 || size2 == 0) {
        printf("Error reading datasets.\n");
        return 1;
    }

    // Statistical analysis for Dataset 1
    double mean1 = calculate_mean(dataset1, size1);
    double median1 = calculate_median(dataset1, size1);
    double std_dev1 = calculate_std_dev(dataset1, size1);
    double range1 = calculate_range(dataset1, size1);

    // Statistical analysis for Dataset 2
    double mean2 = calculate_mean(dataset2, size2);
    double median2 = calculate_median(dataset2, size2);
    double std_dev2 = calculate_std_dev(dataset2, size2);
    double range2 = calculate_range(dataset2, size2);

    // Output results
    printf("Dataset 1 - Mean: %.2f, Median: %.2f, Std Dev: %.2f, Range: %.2f\n", mean1, median1, std_dev1, range1);
    printf("Dataset 2 - Mean: %.2f, Median: %.2f, Std Dev: %.2f, Range: %.2f\n", mean2, median2, std_dev2, range2);

    return 0;
}


