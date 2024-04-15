const { faker } = require('@faker-js/faker');
const express = require('express');
const router = express.Router();
const firebaseDb = require('../../FirebaseCredentials');

let Fish = [
    {
        id:"1",
        name: "Red Crowntail Beta Fish",
        origin:  "South Asia",
        species: "B. splendens",
        beauty_score:9.8
    },
    {
        id:"2",
        name: "Discus Fish",
        origin:  "Amazon River",
        species: "Symphysodon discus",
        beauty_score:9.5
    },
    {
        id:"3",
        name: "Banggai Cardinalfish",
        origin:  "Banggai Archipelago",
        species: "P. kauderni",
        beauty_score:8.8
    },
    {
        id:"4",
        name: "Mandarinfish",
        origin:  "Pacific Ocean",
        species: "S. splendidus",
        beauty_score:6.8
    },
    {
        id:"5",
        name: "Ram Cichlid Fish",
        origin:  "Orinoco River",
        species: "M. ramirezi",
        beauty_score:7.7
    },
];

async function generateFishData(numFish,Id) {
    const fishData = [];

    for (let i = 0; i < numFish; i++) {
        await addDoc(collection(firebaseDb.FIREBASE_DB,'FishTanks',Id,'Fish'),{
            id: faker.string.uuid(),
            name: faker.commerce.productName(), 
            origin: faker.location.country(),
            species: faker.lorem.word(),
            beauty_score: parseFloat(faker.string.numeric(2, { bannedDigits: ['0'], allowLeadingZeros: false })) / 10
        });
    }

    return fishData;
}

//const fishData = generateFishData(100);
//fishData.map(fish =>{
   // Fish.push(fish);
//});

router.get('/', (req, res, next) => {
    const fishArray = Fish.map(fish => ({
        id: fish.id,
        name: fish.name,
        species: fish.species,
        origin: fish.origin,
        beauty_score: fish.beauty_score
    }));
    
    res.status(200).json(fishArray);
});

router.post('/',(req,res,next)=>{
    const fish = {
        id:parseInt(req.body.id),
        name:req.body.name,
        species:req.body.species,
        origin:req.body.origin,
        beauty_score:parseFloat(req.body.beauty_score)
    }
    Fish.push(fish);
    res.status(200).json({
        message: "fish added succesfully"
    });
});

router.put('/:fishId',(req,res,next)=>{
        const id = req.params.fishId;
        var found = false;
        for(var i = 0;i<Fish.length;++i){
            if(Fish[i].id == id){
                Fish[i].name = req.body.name;
                Fish[i].species = req.body.species;
                Fish[i].origin = req.body.origin;
                Fish[i].beauty_score = parseFloat(req.body.beauty_score);
                found = true;
            }
        }   
        if(!found){
            res.status(404).json({
                message: `Fish ${id} not found`
            });
        }
        else{
            res.status(200).json({
                message: `Fish ${id} updated`
            });
        }
});

router.delete('/:fishId',(req,res,next) =>{
    const id = req.params.fishId;
    for(var i = 0;i<Fish.length;++i){
        if(Fish[i].id == id){
            Fish.splice(i,1);
            res.status(200).json({
                message: `Deleted fish ${id}`
            });
        }
    }
});

router.get('/:fishId',(req,res,next) =>{
    const id = req.params.fishId;
    for(var i = 0;i<Fish.length;++i)
        if(Fish[i].id == id){
            res.status(200).json({
                id:Fish[i].id,
                name:Fish[i].name,
                species:Fish[i].species,
                origin:Fish[i].origin,
                beauty_score:Fish[i].beauty_score
            });
        }
});

module.exports = router;
