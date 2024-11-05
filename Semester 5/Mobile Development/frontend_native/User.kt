package com.example.myapplication

data class User (
    val id : Long,
    val username: String,
    val email:  String,
    val savedRecipes: MutableList<Recipe>
    )