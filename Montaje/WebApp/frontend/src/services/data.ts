import axios from "axios"
import { serializeError } from "../utils";
import { z } from "zod";
import { Data, DataWithId, dataWithIdSchema } from "../types/data";

const instance = axios.create({
    baseURL: "/api/users/data",
    headers: {
        "Authorization": `Bearer ${localStorage.getItem("token")}`,
        "Content-Type": "application/json"
    }
});

export const getAll = async () => {
    try {
        const { data } = await instance.get("/");
        return z.array(dataWithIdSchema).parse(data);
    } catch (error) {
        console.error("Error in get all data", serializeError(error));
        throw error;
    }
}

export const getOne = async (id: number) => {
    try {
        const { data } = await instance.get(`/${id}`);
        return dataWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in get one data", serializeError(error));
        throw error;
    }
}

export const createOne = async (entry: Data) => {
    try {
        const { data } = await instance.post("/", entry);
        return dataWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in create one data", serializeError(error));
        throw error;
    }
}

export const updateOne = async (entry: DataWithId) => {
    try {
        const { data } = await instance.put(`/${entry.id}`, entry)
        return dataWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in update one data", serializeError(error));
        throw error;
    }
}

export const deleteOne = async (id: number) => {
    try {
        await instance.delete(`/${id}`);
    } catch (error) {
        console.error("Error in delete one data", serializeError(error));
        throw error;
    }
}