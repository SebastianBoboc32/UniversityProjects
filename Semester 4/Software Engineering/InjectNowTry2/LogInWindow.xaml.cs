using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows;

namespace InjectNowGui
{
    public partial class LogInWindow : Window
    {
        public LogInWindow()
        {
            InitializeComponent();
        }

        private void SignInButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordTextBox.Text; // Consider hashing the password for comparison
            // string email = EmailTextBox.Text; // Uncomment if you use email as part of login

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                MessageBox.Show("Please enter both username and password.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (AuthenticateUser(username, password))
            {
                MessageBox.Show("Login successful!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                // Proceed to the next window or dashboard
            }
            else
            {
                MessageBox.Show("Login failed. Please check your username and password.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

            MainMenuWindow mainMenuWindow = new MainMenuWindow();
            mainMenuWindow.Show();
            this.Close();
        }

        private bool AuthenticateUser(string username, string password)
        {
            string connectionString = "";
            bool isAuthenticated = false;

            using (SqlConnection con = new SqlConnection(connectionString))
            {
                try
                {
                    con.Open();
                    string query = "SELECT COUNT(1) FROM UserAccounts WHERE Username=@Username AND Password=@Password"; // Ensure Passwords are hashed and compare hashes
                    using (SqlCommand cmd = new SqlCommand(query, con))
                    {
                        cmd.Parameters.AddWithValue("@Username", username);
                        cmd.Parameters.AddWithValue("@Password", password); // Use hashed password for comparison

                        isAuthenticated = Convert.ToInt32(cmd.ExecuteScalar()) == 1;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Failed to connect to database. Error: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

            return isAuthenticated;
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            SignUpPage signUpPage = new SignUpPage();
            signUpPage.Show();
            this.Close();
        }
    }
}