package com.example.myapplication
import android.os.Parcelable
import kotlinx.parcelize.Parcelize

@Parcelize
data class Recipe (
    val id: Long,
    val title:String,
    val ingredients: List<String>,
    val instructions: String,
    val category: String,
    val cookTime: Int
) : Parcelable

