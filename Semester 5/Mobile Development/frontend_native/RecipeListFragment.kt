package com.example.myapplication

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.Observer
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.myapplication.databinding.FragmentRecipeListBinding

class RecipeListFragment : Fragment() {

    private var _binding: FragmentRecipeListBinding? = null
    private val binding get() = _binding!!
    private val recipeViewModel: RecipeViewModel by activityViewModels()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentRecipeListBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // Initialize RecyclerView and Adapter with click listener
        val recipeAdapter = RecipeAdapter { recipe ->
            // Create a Bundle to pass the Recipe object
            val bundle = Bundle().apply {
                putParcelable("recipe", recipe) // Make sure Recipe implements Parcelable
            }
            // Navigate with the Bundle
            findNavController().navigate(R.id.updateRecipeFragment, bundle)
        }

        binding.recyclerView.layoutManager = LinearLayoutManager(context)
        binding.recyclerView.adapter = recipeAdapter

        // Observe the recipes LiveData and update the adapter's list
        recipeViewModel.recipes.observe(viewLifecycleOwner, Observer { recipes ->
            println("Recipes observed with size: ${recipes.size}") // Log to confirm size
            recipeAdapter.submitList(recipes)
        })

    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}