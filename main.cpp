#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#include <iostream>

#include "Account.h"
#include <filesystem>

using namespace std;
using namespace std::chrono;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    Account myAccount("Joan");

    Date d1(2025,1, 10);
    Date d2(2025, 1, 12);
    Date d3(2025, 1, 15);

    Transaction t1(TransactionType::Income, 1500.0,d1,"Stipendio di gennaio" , "Lavoro");
    Transaction t2(TransactionType::Income, 40.0,d1,"Babysitting" , "Lavoro");
    Transaction t3(TransactionType::Expense,80.0,d2,"Spesa al supermercato","Spesa");
    Transaction t4(TransactionType::Expense,500.0,d3,"Affitto gennaio","Casa");

    myAccount.addTransaction(t3);
    myAccount.addTransaction(t4);
    myAccount.addTransaction(t1);
    myAccount.addTransaction(t2);

    cout << "Conto di: " << myAccount.getOwnerName() << "\n";
    cout << "\nSaldo attuale: " << myAccount.getBalance() << endl;

    const auto& transactions = myAccount.getTransactions();
    cout << "Numero di transazioni: " << transactions.size() << "\n";

    cout << "Dettaglio transazioni:\n";
    for (const auto& t : transactions) {
        t.toString(true);
    }
    //per mettere il colore ho abilitato la voce "Emulate terminal in output console"
    cout << "=== SALVATAGGIO SU FILE ===\n";
    myAccount.saveToFile("conto.txt");
    cout << "File 'conto.txt' salvato correttamente.\n\n";

    cout << "=== CARICAMENTO DA FILE ===\n";
    Account loaded("Vuoto");
    loaded.loadFromFile("conto.txt");

    cout << "Proprietario caricato: "
         << loaded.getOwnerName() << "\n";

    cout << "Transazioni caricate:\n";
    for (const auto& t : loaded.getTransactions()) {
        t.toString(false); // stampa normale, senza colori
    }

    cout << "\nSaldo dopo il caricamento: "
         << loaded.getBalance() << "\n";

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.