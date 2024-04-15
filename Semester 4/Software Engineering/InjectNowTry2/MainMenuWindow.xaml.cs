using InjectNow;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace InjectNowGui
{

    public class Product
    {
        public int DrugID { get; set; } // Assuming this is an identifier for each product
        public string DrugName { get; set; }
        public string Category { get; set; }
        public decimal Price { get; set; } // New property
        public int Quantity { get; set; } = 1; // Default quantity
        public int ProductTypeID { get; set; } // New property
    }
    public partial class MainMenuWindow : Window
    {
        public MainMenuWindow()
        {
            InitializeComponent();
            LoadAllProducts();
        }

        string getConnectionString()
        {
            return "";
        }

        private void LoadAllProducts()
        {
            string connectionString = getConnectionString();
            List<Product> products = new List<Product>();

            using (SqlConnection con = new SqlConnection(connectionString))
            {
                try
                {
                    con.Open();
                    string sqlQuery = "SELECT DrugName, Category FROM Product";
                    SqlCommand cmd = new SqlCommand(sqlQuery, con);
                    SqlDataReader reader = cmd.ExecuteReader();
                    MessageBox.Show("aaaaa");
                    while (reader.Read())
                    {
                        
                        products.Add(new Product
                        {
                            DrugName = reader["DrugName"].ToString(),
                            Category = reader["Category"].ToString()
                        });
                    }
                    foreach (Product product in products)
                    {
                        Console.WriteLine(product);
                    }
                    DrugListListView.ItemsSource = products;
                    reader.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

        }

        private void SearchButton_Click(object sender, RoutedEventArgs e)
        {
            string connectionString = getConnectionString();
            string searchQuery = SearchbarTextBox.Text;
            List<Product> products = new List<Product>();

            using (SqlConnection con = new SqlConnection(connectionString))
            {
                try
                {
                    con.Open();
                    string sqlQuery = "SELECT DrugName, Category FROM Product";
                    SqlCommand cmd = new SqlCommand(sqlQuery, con);
                    SqlDataReader reader = cmd.ExecuteReader();

                    while (reader.Read())
                    {
                        products.Add(new Product
                        {
                            DrugName = reader["DrugName"].ToString(),
                            Category = reader["Category"].ToString()
                        });
                    }

                    DrugListListView.ItemsSource = products;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void AddToCartButton_Click(object sender, RoutedEventArgs e)
        {
            if (DrugListListView.SelectedItem is Product selectedProduct)
            {
                string connectionString = getConnectionString();
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    try
                    {
                        con.Open();
                        string insertQuery = @"INSERT INTO CartProduct (DrugID, DrugName, Price, Category, Quantity, ProductTypeID)
                                       VALUES (@DrugID, @DrugName, @Price, @Category, @Quantity, @ProductTypeID)";

                        SqlCommand cmd = new SqlCommand(insertQuery, con);
                        cmd.Parameters.AddWithValue("@DrugID", selectedProduct.DrugID);
                        cmd.Parameters.AddWithValue("@DrugName", selectedProduct.DrugName);
                        cmd.Parameters.AddWithValue("@Price", selectedProduct.Price);
                        cmd.Parameters.AddWithValue("@Category", selectedProduct.Category);
                        cmd.Parameters.AddWithValue("@Quantity", selectedProduct.Quantity);
                        cmd.Parameters.AddWithValue("@ProductTypeID", selectedProduct.ProductTypeID);

                        int result = cmd.ExecuteNonQuery();
                        // Check result to see if the row was added successfully
                        if (result > 0)
                        {
                            MessageBox.Show("Product added to cart successfully!");
                        }
                        else
                        {
                            MessageBox.Show("Failed to add product to cart.");
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Error: " + ex.Message);
                    }
                }
            }
            else
            {
                MessageBox.Show("Please select a product to add to cart.");
            }
        }

        private void CartButton_Click_1(object sender, RoutedEventArgs e)
        {
            Cart cart = new Cart();
            cart.Show();
            this.Close();

        }
    }
}

