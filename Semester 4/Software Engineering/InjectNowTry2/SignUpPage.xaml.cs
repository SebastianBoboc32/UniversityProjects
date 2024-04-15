using System;
using System.Collections.Generic;
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
using UserManagement;
using System.Data.SqlClient;
using System.Data;

namespace InjectNowGui
{
    /// <summary>
    /// Interaction logic for SignUpPage.xaml
    /// </summary>
    public partial class SignUpPage : Window
    {
        SqlConnection con;
        SqlDataAdapter daUsers;
        SqlDataAdapter daTransactions;
        DataSet dset;

        SqlCommandBuilder cmdBuilder;

        public SignUpPage()
        {
            InitializeComponent();
        }

        string getConnectionString()
        {
            return "";
        }

        void InitializeConn()
        {
            try
            {
                con = new SqlConnection(getConnectionString());
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            string username = SignUpUsernameTextBox.Text;
            string password = SignUpPasswordTextBox.Text; // Consider hashing the password before storing
            string confirmPassword = SignUpConfirmPasswordTextBox.Text;
            string email = SignUpEmailTextBox.Text;
            string accountType = ((ComboBoxItem)SignUpAccountTypeComboBox.SelectedItem)?.Content.ToString();
            string walletId = " ";

            // Perform validation
            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password) || string.IsNullOrEmpty(confirmPassword) || string.IsNullOrEmpty(email) || string.IsNullOrEmpty(accountType))
            {
                MessageBox.Show("Please fill in all fields.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (password != confirmPassword)
            {
                MessageBox.Show("Passwords do not match.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!IsValidEmail(email))
            {
                MessageBox.Show("Invalid email address.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            // Assuming validation passed, insert the new user into the database
            try
            {
                InitializeConn();
                con.Open();

                //string hashedPassword = HashPassword(password); // Implement this method based on your hashing preference

                string insertQuery = "INSERT INTO UserAccounts (Username, Password, Email, AccountType,WalletID) VALUES (@Username, @Password, @Email, @AccountType,@walletId)";
                using (SqlCommand cmd = new SqlCommand(insertQuery, con))
                {
                    cmd.Parameters.AddWithValue("@Username", username);
                    cmd.Parameters.AddWithValue("@Password", password);
                    cmd.Parameters.AddWithValue("@Email", email);
                    cmd.Parameters.AddWithValue("@AccountType", accountType);
                    cmd.Parameters.AddWithValue("@WalletId", walletId);
                    int result = cmd.ExecuteNonQuery();

                    // Check Error
                    if (result < 0)
                        MessageBox.Show("Error inserting data into Database!");
                    else
                        MessageBox.Show("Account created successfully.", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to insert data. Error: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            finally
            {
                if (con != null && con.State == ConnectionState.Open)
                {
                    con.Close();
                }
            }

            // Proceed to log in window
            LogInWindow logInWindow = new LogInWindow();
            logInWindow.Show();
            this.Close();
        }
        private bool IsValidEmail(string email)
        {
            try
            {
                var addr = new System.Net.Mail.MailAddress(email);
                return addr.Address == email;
            }
            catch
            {
                return false;
            }
        }


    }
}
