package com.example.myapplication

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.navigation.fragment.findNavController
import com.example.myapplication.databinding.FragmentUpdateRecipeBinding
import androidx.recyclerview.widget.LinearLayoutManager

class UpdateRecipeFragment : Fragment() {

    private var _binding: FragmentUpdateRecipeBinding? = null
    private val binding get() = _binding!!
    private val recipeViewModel: RecipeViewModel by activityViewModels()

    private lateinit var originalRecipe: Recipe

    private lateinit var recipeAdapter: RecipeAdapter

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentUpdateRecipeBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // Initialize RecyclerView
        recipeAdapter = RecipeAdapter { recipe ->
            // On item click, populate the fields with the selected recipe
            originalRecipe = recipe
            populateFields(recipe)
        }

        binding.recipeListRecyclerView.adapter = recipeAdapter
        binding.recipeListRecyclerView.layoutManager = LinearLayoutManager(requireContext())

        // Observe the recipes from the ViewModel and submit to adapter
        recipeViewModel.recipes.observe(viewLifecycleOwner) { recipes ->
            recipeAdapter.submitList(recipes)
        }

        binding.updateRecipeButton.setOnClickListener {
            updateRecipe()
        }
    }

    private fun populateFields(recipe: Recipe) {
        binding.recipeTitleInput.setText(recipe.title)
        binding.recipeCategoryInput.setText(recipe.category)
        binding.recipeIngredientsInput.setText(recipe.ingredients.joinToString(","))
        binding.recipeTimeInput.setText(recipe.cookTime.toString())
    }

    private fun updateRecipe() {
        if (!::originalRecipe.isInitialized) {
            Toast.makeText(requireContext(), "Please select a recipe to update", Toast.LENGTH_SHORT).show()
            return
        }

        val title = binding.recipeTitleInput.text.toString().trim()
        val category = binding.recipeCategoryInput.text.toString().trim()
        val ingredients = binding.recipeIngredientsInput.text.toString().trim().split(",")
        val cookTimeText = binding.recipeTimeInput.text.toString().trim()
        val instructions = binding.recipeInstructionsInput.text.toString().trim()

        if (title.isEmpty() || category.isEmpty() || ingredients.isEmpty() || cookTimeText.isEmpty()) {
            Toast.makeText(requireContext(), "Please fill all fields", Toast.LENGTH_SHORT).show()
            return
        }

        val cookTime = cookTimeText.toIntOrNull()
        if (cookTime == null) {
            Toast.makeText(requireContext(), "Invalid cook time", Toast.LENGTH_SHORT).show()
            return
        }

        val updatedRecipe = Recipe(
            id = originalRecipe.id, // Keep the original ID
            title = title,
            ingredients = ingredients,
            instructions = instructions, // Or get updated instructions
            category = category,
            cookTime = cookTime
        )
        recipeViewModel.updateRecipe(updatedRecipe)

        findNavController().popBackStack() // Go back to the previous fragment
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}