#include <stdio.h>
#include <string.h>
#define MAX_CARS 100
#define MAX_RENTALS 100

struct Car {
    int id;
    char model[50];
    char status[20];
    char description[100];
    char couleur[20];
    int anneeFabrication;
};

struct Rental {
    int carId;
    char startDate[20];
    char endDate[20];
};

void printTableHeader() {
    printf("%-4s%-20s%-15s%-20s%-15s%-10s\n", "ID", "Modèle", "État", "Description", "Couleur", "Année");
}

void displayCars(const struct Car cars[], int numCars) {
    printf("\nLa liste de toutes les voitures de l'agence :\n");
    printf("%-4s%-20s%-15s\n", "ID", "Modèle", "État");

    for (int i = 0; i < numCars; i++) {
        printf("%-4d%-20s%-15s\n", cars[i].id, cars[i].model, cars[i].status);
    }
    printf("\n");
}

void rentCar(struct Car cars[], int numCars, struct Rental rentals[], int *numRentals) {
    int carId;
    printf("Entrez l'ID de la voiture que vous souhaitez louer : ");
    scanf("%d", &carId);

    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId && strcmp(cars[i].status, "Disponible") == 0) {
            carIndex = i;
            break;
        }
    }

    if (carIndex != -1) {
        printf("Entrez la date de début de la location (format DD/MM/YYYY) : ");
        scanf("%s", rentals[*numRentals].startDate);

        strcpy(cars[carIndex].status, "Louée");

        rentals[*numRentals].carId = carId;
        (*numRentals)++;
        printf("Location réussie.\n");
    } else {
        printf("La voiture n'est pas disponible pour la location.\n");
    }
}

void displayRentalHistory(const struct Rental rentals[], int numRentals) {
    printf("\nHistorique des locations :\n");
    printf("%-4s%-15s%-15s\n", "ID", "Début", "Fin");
    for (int i = 0; i < numRentals; i++) {
        printf("%-4d%-15s%-15s\n", rentals[i].carId, rentals[i].startDate, rentals[i].endDate);
    }
    printf("\n");
}

void returnCar(struct Car cars[], int numCars, struct Rental rentals[], int numRentals) {
    int carId;
    printf("Entrez l'ID de la voiture à retourner : ");
    scanf("%d", &carId);

    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId && strcmp(cars[i].status, "Louée") == 0) {
            carIndex = i;
            break;
        }
    }

    if (carIndex != -1) {
        printf("Entrez la date de fin de la location (format DD/MM/YYYY) : ");
        scanf("%s", rentals[numRentals - 1].endDate);

        strcpy(cars[carIndex].status, "Disponible");
        printf("Retour de la voiture réussi.\n");
    } else {
        printf("La voiture n'est pas actuellement louée.\n");
    }
}

void displayCarDescription(const struct Car cars[], int numCars) {
    int carId;
    printf("Entrez l'ID de la voiture pour afficher sa description : ");
    scanf("%d", &carId);

    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId) {
            carIndex = i;
            break;
        }
    }

    if (carIndex != -1) {
        printf("\nDescription de la voiture (ID %d) :\n", carId);
        printf("Modèle          : %s\n", cars[carIndex].model);
        printf("État            : %s\n", cars[carIndex].status);
        printf("Description     : %s\n", cars[carIndex].description);
        printf("Couleur         : %s\n", cars[carIndex].couleur);
        printf("Année           : %d\n", cars[carIndex].anneeFabrication);
    } else {
        printf("Aucune voiture avec cet ID n'a été trouvée.\n");
    }
}

void removeDefectiveCar(struct Car cars[], int *numCars) {
    int carId;
    printf("Entrez l'ID de la voiture en panne à supprimer : ");
    scanf("%d", &carId);

    int carIndex = -1;
    for (int i = 0; i < *numCars; i++) {
        if (cars[i].id == carId && strcmp(cars[i].status, "En panne") == 0) {
            carIndex = i;
            break;
        }
    }

    if (carIndex != -1) {
        for (int i = carIndex; i < *numCars - 1; i++) {
            cars[i] = cars[i + 1];
        }
        (*numCars)--;
        printf("La voiture en panne a été supprimée avec succès.\n");
    } else {
        printf("Aucune voiture en panne avec cet ID n'a été trouvée.\n");
    }
}

void fileComplaintAndReturn(struct Car cars[], int numCars, struct Rental rentals[], int numRentals) {
    int carId;
    printf("Entrez l'ID de la voiture à réclamer et retourner : ");
    scanf("%d", &carId);

    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId && strcmp(cars[i].status, "Louée") == 0) {
            carIndex = i;
            break;
        }
    }

    if (carIndex != -1) {
        printf("Entrez la date de fin de la location (format DD/MM/YYYY) : ");
        scanf("%s", rentals[numRentals - 1].endDate);

        strcpy(cars[carIndex].status, "À réparer");
        printf("Réclamation enregistrée, la voiture a été retournée à l'agence.\n");
    } else {
        printf("Aucune voiture louée avec cet ID n'a été trouvée.\n");
    }
}

int main() {
    struct Car cars[MAX_CARS];
    int numCars = 0;

    struct Rental rentals[MAX_RENTALS];
    int numRentals = 0;
    cars[numCars++] = (struct Car){101, "Toyota Camry", "Disponible", "Berline, 4 portes", "Bleu métallisé", 2022};
    cars[numCars++] = (struct Car){102, "Honda Accord", "En panne", "Berline, 4 portes", "Gris anthracite", 2023};
    cars[numCars++] = (struct Car){103, "Ford Mustang", "Louée", "Voiture de sport, 2 portes", "Rouge vif", 2021};
    cars[numCars++] = (struct Car){104, "Chevrolet Cruze", "En panne", "Compacte, 4 portes", "Blanc", 2022};
    cars[numCars++] = (struct Car){105, "Nissan Altima", "Disponible", "Berline, 4 portes", "Noir", 2023};
    cars[numCars++] = (struct Car){106, "BMW X5", "Louée", "VUS, 5 portes", "Argent", 2020};
    cars[numCars++] = (struct Car){107, "Hyundai Elantra", "Disponible", "Compacte, 4 portes", "Vert foncé", 2022};
    cars[numCars++] = (struct Car){108, "Mercedes-Benz C-Class", "En panne", "Berline, 4 portes", "Bleu nuit", 2021};
    cars[numCars++] = (struct Car){109, "Kia Sportage", "Disponible", "SUV, 5 portes", "Gris clair", 2022};
    cars[numCars++] = (struct Car){110, "Audi Q7", "En panne", "VUS, 7 places", "Blanc perle", 2023};
    cars[numCars++] = (struct Car){111, "Jeep Wrangler", "Louée", "VUS, décapotable, 2 portes", "Orange", 2022};
    cars[numCars++] = (struct Car){112, "Volkswagen Golf", "En panne", "Compacte, 4 portes", "Rouge foncé", 2021};
    cars[numCars++] = (struct Car){113, "Subaru Outback", "En panne", "VUS, 5 portes", "Gris foncé", 2020};
    cars[numCars++] = (struct Car){114, "Mazda CX-5", "Louée", "VUS, 5 portes", "Gris foncé", 2020};
    cars[numCars++] = (struct Car){115, "Toyota Prius", "Disponible", "Hybride, 5 portes", "Blanc perle", 2022};
    cars[numCars++] = (struct Car){116, "Ford Explorer", "Disponible", "VUS, 7 places", "Marron", 2023};
    cars[numCars++] = (struct Car){117, "Chevrolet Malibu", "En panne", "Berline, 4 portes", "Bleu ciel", 2021};
    cars[numCars++] = (struct Car){118, "Honda CR-V", "Disponible", "SUV, 5 portes", "Rouge métallisé", 2022};
    cars[numCars++] = (struct Car){119, "Lexus RX", "Disponible", "SUV, 5 portes", "Noir", 2023};
    cars[numCars++] = (struct Car){120, "Volvo XC60", "Disponible", "SUV, 5 portes", "Blanc", 2021};
    cars[numCars++] = (struct Car){121, "Tesla Model 3", "En panne", "Berline électrique, 4 portes", "Noir", 2020};
    cars[numCars++] = (struct Car){122, "Jaguar F-PACE", "En panne", "VUS, 5 portes", "Gris métallisé", 2022};
    cars[numCars++] = (struct Car){123, "Acura MDX", "Disponible", "VUS, 7 places", "Bleu marine", 2023};
    cars[numCars++] = (struct Car){124, "Buick Encore", "Louée", "VUS, 5 portes", "Argent", 2021};
    cars[numCars++] = (struct Car){125, "Chrysler Pacifica", "Disponible", "VUS, 7 places", "Rouge métallisé", 2022};
    cars[numCars++] = (struct Car){126, "GMC Terrain", "En panne", "SUV, 5 portes", "Vert olive", 2020};
    cars[numCars++] = (struct Car){127, "Infiniti Q50", "Louée", "Berline, 4 portes", "Bleu royal", 2023};
    cars[numCars++] = (struct Car){128, "Land Rover Range Rover", "Disponible", "VUS, 5 portes", "Noir profond", 2021};
    cars[numCars++] = (struct Car){129, "Mitsubishi Outlander", "Disponible", "SUV, 5 portes", "Gris argent", 2022};
    cars[numCars++] = (struct Car){130, "Porsche Cayenne", "En panne", "SUV, 5 portes", "Rouge vif", 2023};

    int choice;
    do {
        printf("1. Afficher la liste de toutes les voitures de l'agence\n");
        printf("2. Louer une voiture\n");
        printf("3. Afficher l'historique des locations\n");
        printf("4. Retourner une voiture\n");
        printf("5. Afficher la description d'une voiture\n");
        printf("6. Supprimer une voiture en panne\n");
        printf("7. Réclamer une voiture défaillante\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCars(cars, numCars);
                break;
            case 2:
                rentCar(cars, numCars, rentals, &numRentals);
                break;
            case 3:
                displayRentalHistory(rentals, numRentals);
                break;
            case 4:
                returnCar(cars, numCars, rentals, numRentals);
                break;
            case 5:
                displayCarDescription(cars, numCars);
                break;
            case 6:
                removeDefectiveCar(cars, &numCars);
                break;
            case 7:
                fileComplaintAndReturn(cars, numCars, rentals, numRentals);
                break;
            case 0:
                printf("Merci d'avoir utilisé E-Cars. Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 0);

    return 0;
}
