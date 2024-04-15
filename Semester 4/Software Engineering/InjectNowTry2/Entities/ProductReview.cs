using ProductManagement;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UserManagement;

namespace ProductReviewManagement
{
    public class ProductReview
    {
        // Fields
        private string username;
        private string drugname;
        private int rating;
        private string description;

        // Constructor
        public ProductReview(string username, string drugname, int rating, string description)
        {
            Username = username;
            Drugname = drugname;
            Rating = rating;
            Description = description;
        }

        // Properties with getters and setters
        public string Username
        {
            get { return username; }
            set { username = value; }
        }

        public string Drugname
        {
            get { return drugname; }
            set { drugname = value; }
        }

        public int Rating
        {
            get { return rating; }
            set
            {
                // Validate rating (assumed to be between 1 and 5)
                if (value >= 1 && value <= 5)
                    rating = value;
                else
                    throw new ArgumentOutOfRangeException("Rating must be between 1 and 5.");
            }
        }

        public string Description
        {
            get { return description; }
            set { description = value; }
        }

        // Helper methods to check if username and drugname exist
        private bool UserExists(string username, List<UserAccount> userAccounts)
        {
            // Iterate over the list of user accounts
            foreach (var user in userAccounts)
            {
                // Check if the current user's username matches the provided username
                if (user.Username.Equals(username, StringComparison.OrdinalIgnoreCase))
                {
                    // Username found, return true
                    return true;
                }
            }

            // Username not found in any user account
            return false;
        }

        private bool DrugExists(string drugname, List<Product> products)
        {
            // Iterate over the list of products
            foreach (var product in products)
            {
                // Check if the current product's drug name matches the provided drugname
                if (product.DrugName.Equals(drugname, StringComparison.OrdinalIgnoreCase))
                {
                    // Drug name found, return true
                    return true;
                }
            }

            // Drug name not found in any product
            return false;
        }

    }
}
