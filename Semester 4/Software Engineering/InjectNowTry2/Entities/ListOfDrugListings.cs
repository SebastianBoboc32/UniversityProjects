using System;
using System.Collections.Generic;
using System.Linq;
using DrugListingManagement;
using ProductManagement;
using ProductReviewManagement;
using ListOfProductReviewsManagement;

namespace ListOfDrugListingsManagement
{
    public class ListOfDrugListings
    {
        private List<DrugListings> drugListings;

        public ListOfDrugListings(List<DrugListings> drugListings)
        {
            this.drugListings = drugListings;
        }

        // Create a new drug listing
        public void AddDrugListing(DrugListings drugListing)
        {
            drugListings.Add(drugListing);
            Console.WriteLine("Drug listing added successfully!");
        }

        // Read all drug listings
        public List<DrugListings> GetAllDrugListings()
        {
            return drugListings;
        }

        public void UpdateDrugListing(DrugListings updatedListing)
        {
            // Find the index of the drug listing to update
            int index = drugListings.FindIndex(listing => listing == updatedListing);

            // If the drug listing is found, update it
            if (index != -1)
            {
                drugListings[index] = updatedListing;
                Console.WriteLine("Drug listing updated successfully!");
            }
            else
            {
                Console.WriteLine("Drug listing not found.");
            }
        }

        // Delete a drug listing
        public void DeleteDrugListing(DrugListings listingToDelete)
        {
            // Find the index of the drug listing to delete
            int index = drugListings.FindIndex(listing => listing == listingToDelete);

            // If the drug listing is found, remove it
            if (index != -1)
            {
                drugListings.RemoveAt(index);
                Console.WriteLine("Drug listing deleted successfully!");
            }
            else
            {
                Console.WriteLine("Drug listing not found.");
            }
        }


        // Search for drugs across all listings
        public List<Product> Search(string keyword)
        {
            List<Product> searchResults = new List<Product>();
            foreach (var listing in drugListings)
            {
                foreach (var drug in listing.drugs)
                {
                    if (drug.DrugName.ToLower().Contains(keyword.ToLower()))
                    {
                        searchResults.Add(drug);
                    }
                }
            }
            return searchResults;
        }

        // Filter drug listings by category
        public List<Product> FilterByCategory(string category)
        {
            List<Product> filteredDrugs = new List<Product>();
            foreach (var listing in drugListings)
            {
                foreach (var drug in listing.drugs)
                {
                    if (drug.Category.Type.ToLower() == category.ToLower())
                    {
                        filteredDrugs.Add(drug);
                    }
                }
            }
            return filteredDrugs;
        }

        // Filter drug listings by price range
        public List<Product> FilterByPrice(double minPrice, double maxPrice)
        {
            List<Product> filteredDrugs = new List<Product>();
            foreach (var listing in drugListings)
            {
                foreach (var drug in listing.drugs)
                {
                    if (drug.Price >= minPrice && drug.Price <= maxPrice)
                    {
                        filteredDrugs.Add(drug);
                    }
                }
            }
            return filteredDrugs;
        }

        // Filter drug listings by rating (not implemented in this example)
        /*public List<Product> FilterByRating(double minRating)
        {
            List<Product> filteredDrugs = new List<Product>();
            foreach (var listing in drugListings)
            {
                foreach (var drug in listing.drugs)
                {
                    // Check if the drug has associated reviews
                    if (drug(review => review.Drugname.Equals(drug.DrugName, StringComparison.OrdinalIgnoreCase)))
                    {
                        // Calculate the average rating for the current drug
                        double averageRating = CalculateAverageRating(drug.Reviews, drug.DrugName);

                        // Check if the average rating meets the minimum rating criteria
                        if (averageRating >= minRating)
                        {
                            filteredDrugs.Add(drug);
                        }
                    }
                }
            }
            return filteredDrugs;
        }*/

        /*private double CalculateAverageRating(List<ProductReview> reviews, string drugName)
        {
            // Filter reviews for the specific drug
            var drugReviews = reviews.Where(review => review.Drugname.Equals(drugName, StringComparison.OrdinalIgnoreCase));

            // Check if there are any reviews for the drug
            if (!drugReviews.Any())
            {
                return 0; // No reviews available, return 0 rating
            }

            // Calculate the total rating sum
            int totalRating = 0;
            foreach (var review in drugReviews)
            {
                totalRating += review.Rating;
            }

            // Calculate and return the average rating
            return (double)totalRating / drugReviews.Count();
        }*/

        // Filter drug listings by dealer username
        public List<Product> FilterByDealer(string dealerUsername)
        {
            List<Product> filteredDrugs = new List<Product>();
            foreach (var listing in drugListings)
            {
                if (listing.dealer.Username.ToLower() == dealerUsername.ToLower())
                {
                    filteredDrugs.AddRange(listing.drugs);
                }
            }
            return filteredDrugs;
        }

        // ToString method
        public override string ToString()
        {
            string listingsString = "";
            foreach (var listing in drugListings)
            {
                listingsString += listing.ToString() + "\n";
            }
            return listingsString;
        }
    }
}
