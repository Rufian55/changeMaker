#include <iostream>
using namespace std;

int main() {

	int array[4] = { 3, 7, 7, 12 };

	for (int i = 0; i < 4; i++) {

		// look to the left in the array if the number was used before
		int found = 0;
		for (int j = 0; j < i; j++) {
			if (array[i] == array[j]) found++;
		}

		// go on if it's the first occurance
		if (found == 0) {

			// we know of one occurance
			int count = 1;

			// look to the right in the array for other occurances
			for (int j = i + 1; j < 4; j++) {
				if (array[i] == array[j]) count++;
			}

			cout << array[i] << ":" << count << endl;
		}
	}
	return 0;
}