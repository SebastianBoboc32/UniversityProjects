using ProductManagement;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UserManagement;

namespace OrderManagement
{
    public class Order
    {
        public int OrderID { get; set; }
        public ShoppingCart Cart { get; set; }
        public OrderStatus Status { get; set; }
        public bool Accepted { get; set; }
        public UserAccount DeliveryGuy { get; set; }
        public int DeliverySpeed { get; set; }

        public Order(int orderID, ShoppingCart cart, OrderStatus status, bool accepted, UserAccount deliveryGuy, int deliverySpeed)
        {
            OrderID = orderID;
            Cart = cart;
            Status = status;
            Accepted = accepted;
            DeliveryGuy = deliveryGuy;
            DeliverySpeed = deliverySpeed;
        }

        // Override ToString method to provide a string representation of the Order object
        public override string ToString()
        {
            return $"OrderID: {OrderID}, ShoppingCart: {Cart}, Status: {Status}, Accepted: {Accepted}, DeliveryGuy: {DeliveryGuy}, DeliverySpeed: {DeliverySpeed}";
        }

        // Method to check if the user associated with the order is banned
        public bool CheckIfBanned(UserAccount userAccount)
        {
            if (userAccount.Banned) return true;
            else return false;
        }
    }

    public class ShoppingCart
    {
        public string Username { get; set; }
        public List<Product> ProductsInCart { get; set; }
        public double TotalPrice { get; set; }

        public ShoppingCart(string username)
        {
            Username = username;
            ProductsInCart = new List<Product>();
            TotalPrice = 0;
        }

        public void AddProduct(Product product)
        {
            ProductsInCart.Add(product);
            TotalPrice += product.Price;
        }

        public void RemoveProduct(Product product)
        {
            ProductsInCart.Remove(product);
            TotalPrice -= product.Price;
        }

        // Calculate the total price of all products in the shopping cart
        public double ComputeTotalPrice()
        {
            double totalPrice = 0;
            foreach (Product product in ProductsInCart)
            {
                totalPrice += product.Price;
            }
            return totalPrice;
        }

        // Convert the shopping cart to a string representation
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine($"Username: {Username}");
            sb.AppendLine("Products in Cart:");
            foreach (Product product in ProductsInCart)
            {
                sb.AppendLine($"- {product.DrugName}, Price: {product.Price:C}");
            }
            sb.AppendLine($"Total Price: {TotalPrice:C}");
            return sb.ToString();
        }
    }

    public class OrderStatus
    {
        public string Location { get; set; }
        public string Status { get; set; }

        public OrderStatus(string location, string status)
        {
            Location = location;
            Status = status;
        }
    }

    public class OrderHistory
    {
        private List<Order> allOrders;

        public OrderHistory()
        {
            allOrders = new List<Order>();
        }

        // Method to add an order to the order history
        public void AddOrder(Order order)
        {
            allOrders.Add(order);
        }

        // Method to get all orders in the order history
        public List<Order> GetAllOrders()
        {
            return allOrders;
        }
    }
}
