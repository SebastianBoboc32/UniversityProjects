using InjectNowGui;
using ProductManagement;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Windows;

namespace InjectNow
{
    public partial class Cart : Window
    {
        public Cart()
        {
            InitializeComponent();
            LoadCartProducts();
        }

        public class Product
        {
            public int DrugID { get; set; } // Assuming this is an identifier for each product
            public string DrugName { get; set; }
            public string Category { get; set; }
            public decimal Price { get; set; } // New property
            public int Quantity { get; set; } = 1; // Default quantity
            public int ProductTypeID { get; set; } // New property
        }

        private void LoadCartProducts()
        {
            string connectionString = "";
            List<Product> cartProducts = new List<Product>();

            using (SqlConnection con = new SqlConnection(connectionString))
            {
                try
                {
                    con.Open();
                    string sqlQuery = "SELECT * FROM CartProduct"; // Adjust the query to match your needs
                    SqlCommand cmd = new SqlCommand(sqlQuery, con);
                    SqlDataReader reader = cmd.ExecuteReader();

                    while (reader.Read())
                    {
                        cartProducts.Add(new Product
                        {
                            DrugID = Convert.ToInt32(reader["DrugID"]),
                            DrugName = reader["DrugName"].ToString(),
                            Category = reader["Category"].ToString(),
                            Price = Convert.ToDecimal(reader["Price"]),
                            Quantity = Convert.ToInt32(reader["Quantity"]),
                            ProductTypeID = reader.IsDBNull(reader.GetOrdinal("ProductTypeID")) ? 0 : Convert.ToInt32(reader["ProductTypeID"])
                            // Adjust the above line if ProductTypeID can be null
                        });
                    }
                    CartListView.ItemsSource = cartProducts;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void CheckoutButton_Click(object sender, RoutedEventArgs e)
        {
            if (CartListView.SelectedItem is Product selectedProduct)
            {
                string connectionString = "";
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    try
                    {
                        con.Open();
                        string deleteQuery = "DELETE FROM CartProduct WHERE DrugID = @DrugID";
                        SqlCommand cmd = new SqlCommand(deleteQuery, con);
                        cmd.Parameters.AddWithValue("@DrugID", selectedProduct.DrugID);

                        int result = cmd.ExecuteNonQuery();
                        if (result > 0)
                        {
                            MessageBox.Show("Product removed from cart.");
                            // Optionally, you could refresh the ListView to show the remaining items
                            LoadCartProducts();
                        }
                        else
                        {
                            MessageBox.Show("Product could not be removed from cart.");
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Error during checkout: " + ex.Message);
                    }
                }
            }
            else
            {
                MessageBox.Show("Please select a product to checkout.");
            }
        }

        private void BackToMainMenuButton_Click(object sender, RoutedEventArgs e)
        {
            // Implementation to go back to the main menu
            MessageBox.Show("Go back to the main menu.");
        }
    }
}
