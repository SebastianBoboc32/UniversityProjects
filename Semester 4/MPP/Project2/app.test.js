const request = require('supertest');
const app = require('./app'); 

describe('Fish API tests', () => {
    // Test retrieving all fish
    test('GET /fish should return all fish', async () => {
        const response = await request(app).get('/fish');
        //console.log(response);
        expect(response.status).toBe(200);
        expect(response.body).toBeInstanceOf(Array);
    });

    // Test adding a new fish
    test('POST /fish should add a new fish', async () => {
        const newFish = {
            id: "7", 
            name: "Clownfish",
            origin: "Pacific Ocean",
            species: "Amphiprioninae",
            beauty_score: 8.5
        };
        const response = await request(app)
            .post('/fish')
            .send(newFish);
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toEqual("fish added succesfully");
    });

    // Test updating an existing fish
    test('PUT /fish/:fishId should update a fish', async () => {
        const updatedFishDetails = {
            name: "Updated Clownfish",
            origin: "Updated Pacific Ocean",
            species: "Updated Amphiprioninae",
            beauty_score: 9.0
        };
        const response = await request(app)
            .put('/fish/2') 
            .send(updatedFishDetails);
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toEqual("Fish 2 updated");
    });

    // Test deleting an existing fish
    test('DELETE /fish/:fishId should delete a fish', async () => {
        const response = await request(app).delete('/fish/4');
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toEqual("Deleted fish 4");
    });

    // Test retrieving a specific fish by ID
    test('GET /fish/:fishId should return a specific fish', async () => {
        const response = await request(app).get('/fish/1'); 
        expect(response.statusCode).toBe(200);
        expect(response.body).toHaveProperty('id', '1');
    });
});