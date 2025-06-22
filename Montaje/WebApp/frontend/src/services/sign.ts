import axios from "axios"
import { serializeError } from "../utils";
import { User } from "../types/user";

const instance = axios.create({
    baseURL: "/api/users/sign",
    headers: {
        "Authorization": localStorage.getItem("token"),
        "Content-Type": "application/json"
    }

});

export const Up = async (user: User) => {
    try {
        await instance.post("/", user);
    } catch (error) {
        console.error("Error in sign up", serializeError(error));
        throw error;
    }
}

export const In = async (user: User) => {
    try {
        const { data } = await instance.put("/", user);
        return data.token;
    } catch (error) {
        console.error("Error sign in ", serializeError(error));
        throw error;
    }
}

export default { Up, In };