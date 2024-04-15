using ProductReviewManagement;
using System;
using System.Collections.Generic;

namespace ListOfProductReviewsManagement
{
    public class ListOfProductReviews
    {
        private List<ProductReview> productReviews;

        public ListOfProductReviews(List<ProductReview> productReviews)
        {
            this.productReviews = productReviews;
        }

        // Add a new product review
        public void AddProductReview(ProductReview review)
        {
            productReviews.Add(review);
            Console.WriteLine("Product review added successfully!");
        }

        // Remove a product review
        public void RemoveProductReview(ProductReview review)
        {
            productReviews.Remove(review);
            Console.WriteLine("Product review removed successfully!");
        }

        // Get all product reviews
        public List<ProductReview> GetAllProductReviews()
        {
            return productReviews;
        }

        // ToString method
        public override string ToString()
        {
            string reviewsString = "";
            foreach (var review in productReviews)
            {
                reviewsString += review.ToString() + "\n";
            }
            return reviewsString;
        }
    }
}
