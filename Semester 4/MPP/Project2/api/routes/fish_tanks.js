const { faker } = require('@faker-js/faker');
const express = require('express');
const router = express.Router();
const firebaseDb = require('../../FirebaseCredentials');

async function generateFishTankData(numFishTanks) {
    const fishTanksData = [];

    for (let i = 0; i < numFishTanks; i++) {
        await addDoc(collection(firebaseDb.FIREBASE_DB,'FishTanks'),{
            Id: faker.string.uuid(),
            TicketPrice: faker.number.int(), 
            location: faker.location.country(),
            reviews: parseFloat(faker.string.numeric(2, { bannedDigits: ['0'], allowLeadingZeros: false })) / 10
        });
    }

    return fishData;
}
