package com.example.myapplication

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.navigation.fragment.findNavController
import com.example.myapplication.databinding.FragmentAddRecipeBinding

class AddRecipeFragment : Fragment() {

    private var _binding: FragmentAddRecipeBinding? = null
    private val binding get() = _binding!!
    private val recipeViewModel: RecipeViewModel by activityViewModels()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentAddRecipeBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.addRecipeButton.setOnClickListener {
            val title = binding.recipeTitleInput.text.toString().trim()
            val category = binding.recipeCategoryInput.text.toString().trim()
            val ingredients = binding.recipeIngredientsInput.text.toString().trim().split(",")
            val cookTimeText = binding.recipeTimeInput.text.toString().trim()

            if (title.isEmpty() || category.isEmpty() || ingredients.isEmpty() || cookTimeText.isEmpty()) {
                Toast.makeText(requireContext(), "Please fill all fields", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val cookTime = cookTimeText.toIntOrNull()
            if (cookTime == null) {
                Toast.makeText(requireContext(), "Invalid cook time", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val newRecipe = Recipe(
                id = System.currentTimeMillis(), // Generate a unique ID
                title = title,
                ingredients = ingredients,
                instructions = "Steps for $title",
                category = category,
                cookTime = cookTime
            )
            recipeViewModel.addRecipe(newRecipe)

            // Use popBackStack to go back to RecipeListFragment
            findNavController().popBackStack()
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}