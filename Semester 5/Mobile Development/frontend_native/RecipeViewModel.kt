package com.example.myapplication

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class RecipeViewModel : ViewModel() {

    private val _recipes = MutableLiveData<List<Recipe>>(
        mutableListOf(
            Recipe(1L,"Spaghetti Carbonara", listOf("spaghetti", "bacon", "eggs", "Parmesan cheese", "black pepper", "salt"),
                "Steps for Carbonara", "Italian", 20),
            Recipe(2L,"Vegetable Stir Fry", listOf("broccoli", "carrots", "bell pepper", "snap peas", "soy sauce", "garlic", "ginger"),
                "Steps for Stir Fry", "Asian", 15),
            Recipe(3L,"Chicken Tikka Masala", listOf("chicken", "yogurt", "onion", "tomato", "garam masala", "ginger", "garlic"),
                "Steps for Tikka Masala", "Indian", 40),
            Recipe(4L,"Beef Tacos", listOf("ground beef", "taco seasoning", "tortillas", "lettuce", "cheese", "tomato", "sour cream"),
                "Steps for Tacos", "Mexican", 25),
            Recipe(5L,"Sushi Rolls", listOf("sushi rice", "nori sheets", "cucumber", "carrot", "avocado", "soy sauce", "wasabi"),
                "Steps for Sushi Rolls", "Japanese", 30),
            Recipe(6L,"French Toast", listOf("bread", "eggs", "milk", "cinnamon", "vanilla extract", "maple syrup"),
                "Steps for French Toast", "American", 15),
            Recipe(7L,"Pad Thai", listOf("rice noodles", "shrimp", "egg", "peanut", "bean sprouts", "lime", "soy sauce"),
                "Steps for Pad Thai", "Thai", 20),
            Recipe(8L,"Greek Salad", listOf("cucumber", "tomato", "feta cheese", "olives", "olive oil", "oregano"),
                "Steps for Greek Salad", "Greek", 10),
            Recipe(9L,"Margherita Pizza", listOf("pizza dough", "tomato sauce", "mozzarella cheese", "basil leaves", "olive oil"),
                "Steps for Margherita Pizza", "Italian", 30),
            Recipe(10L,"Falafel Wrap", listOf("falafel", "pita bread", "lettuce", "tomato", "cucumber", "tahini sauce"),
                "Steps for Falafel Wrap", "Middle Eastern", 20)
        )
    )
    val recipes: LiveData<List<Recipe>> = _recipes

    fun addRecipe(newRecipe: Recipe) {
        val currentList = _recipes.value?.toMutableList() ?: mutableListOf()
        currentList.add(newRecipe)
        _recipes.value = currentList
        println("New recipe added: ${newRecipe.title}")
        println("Updated recipe list: ${_recipes.value?.size}")// Update the LiveData to trigger observers
    }

    fun updateRecipe(updatedRecipe: Recipe) {
        val currentList = _recipes.value?.map {
            if (it.id == updatedRecipe.id) updatedRecipe else it
        } ?: listOf()
        _recipes.value = currentList
    }

    fun deleteRecipe(recipe: Recipe) {
        val currentRecipes = _recipes.value?.toMutableList() ?: mutableListOf()
        currentRecipes.remove(recipe)
        _recipes.value = currentRecipes
    }
}