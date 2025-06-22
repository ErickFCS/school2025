import axios from "axios"
import { serializeError } from "../utils";
import { z } from "zod";
import { Config, ConfigWithId, configWithIdSchema } from "../types/configs";

const instance = axios.create({
    baseURL: "/api/users/config",
    headers: {
        "Authorization": localStorage.getItem("token"),
        "Content-Type": "application/json"
    }
});

export const getAll = async () => {
    try {
        const { data } = await instance.get("/");
        return z.array(configWithIdSchema).parse(data);
    } catch (error) {
        console.error("Error in get all configs", serializeError(error));
        throw error;
    }
}

export const getOne = async (id: number) => {
    try {
        const { data } = await instance.get(`/${id}`);
        return configWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in get one configs", serializeError(error));
        throw error;
    }
}

export const createOne = async (config: Config) => {
    try {
        const { data } = await instance.post("/", config);
        return configWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in create one configs", serializeError(error));
        throw error;
    }
}

export const updateOne = async (config: ConfigWithId) => {
    try {
        const { data } = await instance.put(`/${config.id}`, config)
        return configWithIdSchema.parse(data)
    } catch (error) {
        console.error("Error in update one configs", serializeError(error));
        throw error;
    }
}

export const deleteOne = async (id: number) => {
    try {
        await instance.delete(`/${id}`);
    } catch (error) {
        console.error("Error in delete one configs", serializeError(error));
        throw error;
    }
}