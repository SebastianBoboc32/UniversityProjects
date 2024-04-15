using System;
using System.Collections.Generic;
using UserManagement;
using ProductManagement;


namespace DrugListingManagement
{
    public class DrugListings
    {
        public List<Product> drugs;
        public UserAccount dealer;

        public DrugListings(List<Product> drugs, UserAccount dealer)
        {
            this.drugs = drugs;
            this.dealer = dealer;
        }

        // Create a new drug listing
        public void AddDrug(Product drug)
        {
            drugs.Add(drug);
            Console.WriteLine("Drug added successfully!");
        }

        // Read all drugs in the listing
        public List<Product> GetAllDrugs()
        {
            return drugs;
        }

        // Update an existing drug listing
        public void UpdateDrug(int drugID, Product updatedDrug)
        {
            int index = drugs.FindIndex(d => d.DrugID == drugID);
            if (index != -1)
            {
                drugs[index] = updatedDrug;
                Console.WriteLine("Drug updated successfully!");
            }
            else
            {
                Console.WriteLine("Drug not found!");
            }
        }

        // Delete a drug listing
        public void DeleteDrug(int drugID)
        {
            int index = drugs.FindIndex(d => d.DrugID == drugID);
            if (index != -1)
            {
                drugs.RemoveAt(index);
                Console.WriteLine("Drug deleted successfully!");
            }
            else
            {
                Console.WriteLine("Drug not found!");
            }
        }

        // ToString method
        public override string ToString()
        {
            string drugsString = "";
            foreach (var drug in drugs)
            {
                drugsString += drug.ToString() + "\n";
            }

            return $"Dealer: {dealer.Username}\nDrugs:\n{drugsString}";
        }
    }
}
