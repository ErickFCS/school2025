import { User, UserWithId, userWithIdSchema } from "../types/user";
import { serializeError } from "../utils";
import axios from "axios";
import { z } from "zod";


const instance = axios.create({
    baseURL: "/api/users/users",
    headers: {
        "Authorization": localStorage.getItem("token"),
        "Content-Type": "application/json"
    }
});

export const getAll = async () => {
    try {
        const { data } = await instance.get("/");
        return z.array(userWithIdSchema).parse(data);
    } catch (error) {
        console.error("Error in get all users", serializeError(error));
        throw error;
    }
};

export const getOne = async (id: number) => {
    try {
        const { data } = await instance.get(`/${id}`);
        return userWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in get one user", serializeError(error));
        throw error;
    }
};

export const createOne = async (user: User) => {
    try {
        const { data } = await instance.post("/", user);
        return userWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in create one user", serializeError(error));
        throw error;
    }
};

export const updateOne = async (user: UserWithId) => {
    try {
        const { data } = await instance.put(`/${user.id}`, user);
        return userWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in update one user", serializeError(error));
        throw error;
    }
};

export const deleteOne = async (id: number) => {
    try {
        await instance.delete(`/${id}`);
    } catch (error) {
        console.error("Error in delete one user", serializeError(error));
        throw error;
    }
};
