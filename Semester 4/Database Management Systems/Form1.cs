using System;
using System.Data;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace DBMSForms
{
    public partial class Form1 : Form
    {
        SqlConnection con;
        SqlDataAdapter daUsers;
        SqlDataAdapter daTransactions;
        DataSet dset;
        BindingSource bsUsers;
        BindingSource bsTransactions;

        SqlCommandBuilder cmdBuilder;

        string usersQuery;
        string transactionsQuery;
        

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            try {
                con = new SqlConnection(getConnectionString());
            }catch(SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
            usersQuery = ConfigurationManager.AppSettings["UsersQuery"];
            transactionsQuery = ConfigurationManager.AppSettings["TransactionsQuery"];
            try {
                daUsers = new SqlDataAdapter(usersQuery, con);
                daTransactions = new SqlDataAdapter(transactionsQuery, con);

                dset = new DataSet();
                cmdBuilder = new SqlCommandBuilder(daTransactions);
                daUsers.Fill(dset, ConfigurationManager.AppSettings["UsersTable"]);
                daTransactions.Fill(dset, "Transactions");

                dset.Relations.Add("UsersTransactions",
                    dset.Tables["Users"].Columns["userId"],
                    dset.Tables["Transactions"].Columns["userId"]);

                bsUsers = new BindingSource();
            }
            catch(SqlException ex)
            {
                for(int i = 0; i < ex.Errors.Count; i++)
                {
                    MessageBox.Show(ex.Errors[i].Message);
                }
            }

            bsUsers.DataSource = dset;
            bsUsers.DataMember = "Users";

            bsTransactions = new BindingSource();
            bsTransactions.DataSource = bsUsers; 
            bsTransactions.DataMember = "UsersTransactions"; 

            this.dataGridView1.DataSource = bsUsers; 
            this.dataGridView2.DataSource = bsTransactions;
            cmdBuilder.GetUpdateCommand();
        }

        string getConnectionString()
        {
            return " ";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            daTransactions.Update(dset, "Transactions");
        }
    }
}
