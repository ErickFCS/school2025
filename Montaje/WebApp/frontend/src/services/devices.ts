import { Device, DeviceWithId, deviceWithIdSchema } from "../types/device";
import { serializeError } from "../utils";
import axios from "axios";
import { z } from "zod";


const instance = axios.create({
    baseURL: "/api/users/devices",
    headers: {
        "Authorization": localStorage.getItem("token"),
        "Content-Type": "application/json"
    }
});

export const getAll = async () => {
    try {
        const { data } = await instance.get("/");
        return z.array(deviceWithIdSchema).parse(data);
    } catch (error) {
        console.error("Error in get all devices", serializeError(error));
        throw error;
    }
};

export const getOne = async (id: number) => {
    try {
        const { data } = await instance.get(`/${id}`);
        return deviceWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in get one devices", serializeError(error));
        throw error;
    }
};

export const createOne = async (device: Device) => {
    try {
        const { data } = await instance.post("/", device);
        return deviceWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in create one devices", serializeError(error));
        throw error;
    }
};

export const updateOne = async (device: DeviceWithId) => {
    try {
        const { data } = await instance.put(`/${device.id}`, device);
        return deviceWithIdSchema.parse(data);
    } catch (error) {
        console.error("Error in update one devices", serializeError(error));
        throw error;
    }
};

export const deleteOne = async (id: number) => {
    try {
        await instance.delete(`/${id}`);
    } catch (error) {
        console.error("Error in delete one devices", serializeError(error));
        throw error;
    }
};
