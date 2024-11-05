package com.example.myapplication

import android.os.Bundle
import android.view.*
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.myapplication.databinding.FragmentDeleteRecipeBinding

class DeleteRecipeFragment : Fragment() {

    private var _binding: FragmentDeleteRecipeBinding? = null
    private val binding get() = _binding!!
    private val recipeViewModel: RecipeViewModel by activityViewModels()

    private lateinit var selectedRecipe: Recipe

    private lateinit var recipeAdapter: RecipeAdapter

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentDeleteRecipeBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // Initialize RecyclerView
        recipeAdapter = RecipeAdapter { recipe ->
            // On item click, store the selected recipe
            selectedRecipe = recipe
            // Optional: Provide visual feedback for selection
            recipeAdapter.setSelectedRecipe(recipe)
        }

        binding.recipeListRecyclerView.adapter = recipeAdapter
        binding.recipeListRecyclerView.layoutManager = LinearLayoutManager(requireContext())

        // Observe the recipes from the ViewModel and submit to adapter
        recipeViewModel.recipes.observe(viewLifecycleOwner) { recipes ->
            recipeAdapter.submitList(recipes)
        }

        binding.deleteRecipeButton.setOnClickListener {
            deleteRecipe()
        }
    }

    private fun deleteRecipe() {
        if (!::selectedRecipe.isInitialized) {
            Toast.makeText(requireContext(), "Please select a recipe to delete", Toast.LENGTH_SHORT).show()
            return
        }

        recipeViewModel.deleteRecipe(selectedRecipe)
        Toast.makeText(requireContext(), "Recipe deleted", Toast.LENGTH_SHORT).show()

    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}