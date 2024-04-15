using System;
using System.Collections.Generic;


namespace ProductManagement
{
    public class ProductType
    {
        // Field
        private string type;

        // Property
        public string Type
        {
            get { return type; }
            set { type = value; }
        }

        // Constructor
        public ProductType(string type)
        {
            Type = type;
        }
    }

    public class Product
    {
        // Fields
        private int drugID;
        private string drugName;
        private string description;
        private double price;
        private ProductType category;
        private int quantity;

        // Properties
        public int DrugID
        {
            get { return drugID; }
            set { drugID = value; }
        }

        public string DrugName
        {
            get { return drugName; }
            set { drugName = value; }
        }

        public string Description
        {
            get { return description; }
            set { description = value; }
        }

        public double Price
        {
            get { return price; }
            set { price = value; }
        }

        public ProductType Category
        {
            get { return category; }
            set { category = value; }
        }

        public int Quantity
        {
            get { return quantity; }
            set { quantity = value; }
        }

        // Constructor
        public Product(int drugID, string drugName, string description, double price, ProductType category, int quantity)
        {
            DrugID = drugID;
            DrugName = drugName;
            Description = description;
            Price = price;
            Category = category;
            Quantity = quantity;
        }

        public override string ToString()
        {
            return $"DrugID: {DrugID}, Drug Name: {DrugName}, Description: {Description}, Price: {Price}, Category: {Category.Type}, Quantity: {Quantity}";
        }
    }
}
