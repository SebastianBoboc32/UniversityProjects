package com.example.myapplication

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.databinding.ItemRecipeBinding

class RecipeAdapter(
    private val onRecipeClick: (Recipe) -> Unit // Function parameter for handling item clicks
) : ListAdapter<Recipe, RecipeAdapter.RecipeViewHolder>(RecipeDiffCallback()) {

    // Variable to hold the selected recipe ID
    private var selectedRecipeId: Long? = null

    // Method to set the selected recipe and notify the adapter
    fun setSelectedRecipe(recipe: Recipe) {
        selectedRecipeId = recipe.id
    }

    inner class RecipeViewHolder(private val binding: ItemRecipeBinding) : RecyclerView.ViewHolder(binding.root) {
        fun bind(recipe: Recipe) {
            binding.recipeTitle.text = recipe.title
            binding.recipeCategory.text = recipe.category
            binding.recipeTime.text = "${recipe.cookTime} mins"

            // Set up click listener on the item view
            itemView.setOnClickListener {
                onRecipeClick(recipe)
            }

        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecipeViewHolder {
        val binding = ItemRecipeBinding.inflate(LayoutInflater.from(parent.context), parent, false)
        return RecipeViewHolder(binding)
    }

    override fun onBindViewHolder(holder: RecipeViewHolder, position: Int) {
        holder.bind(getItem(position))
    }
}

class RecipeDiffCallback : DiffUtil.ItemCallback<Recipe>() {
    override fun areItemsTheSame(oldItem: Recipe, newItem: Recipe): Boolean {
        return oldItem.id == newItem.id // Assuming IDs are unique for each recipe
    }

    override fun areContentsTheSame(oldItem: Recipe, newItem: Recipe): Boolean {
        return oldItem == newItem
    }
}