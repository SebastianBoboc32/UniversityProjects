import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getAuth } from "firebase/auth";

const firebaseConfig = {
  apiKey: "",
  authDomain: "",
  projectId: "",
  storageBucket: "",
  messagingSenderId: "",
  appId: "",
  measurementId: ""
};

const FIREBASE_APP = initializeApp(firebaseConfig);
const FIREBASE_AUTH = getAuth(FIREBASE_APP);
const FIREBASE_DB = getFireStore(FIREBASE_APP);

module.exports.FIREBASE_APP = FIREBASE_APP;
module.exports.FIREBASE_AUTH = FIREBASE_AUTH;
module.exports.FIREBASE_DB = FIREBASE_DB;