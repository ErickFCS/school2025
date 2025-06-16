import models from "../../models/Index.js";
import { deviceSchema } from "../../types/device.js";
import { Router } from "express";


const devices = Router();

devices.get("/", async (req, res, next) => {
    try {
        const devices = await models.Esp.findAll();
        res.status(200).json(devices);
    } catch (error) {
        next(error);
    }
});

devices.get("/:id", async (req, res, next) => {
    try {
        const device = await models.Esp.findByPk(req.params.id);
        if (!device) {
            throw new Error(`Device with id: ${req.params.id} not found`);
        }
        res.status(200).json(device);
    } catch (error) {
        next(error);
    }
});

devices.post("/", async (req, res, next) => {
    try {
        const newDevice = new models.Esp(deviceSchema.parse(req.body));
        await newDevice.save();
        res.status(201).json(newDevice);
    } catch (error) {
        next(error);
    }
});

devices.put("/:id", async (req, res, next) => {
    try {
        const device = await models.Esp.findByPk(req.params.id);
        if (!device) {
            throw new Error(`Device with id: ${req.params.id} not found`);
        }
        const updatedDevice = deviceSchema.parse(req.body);
        await device.update(updatedDevice);
        res.status(200).json(device);
    } catch (error) {
        next(error);
    }
});

devices.delete("/:id", async (req, res, next) => {
    try {
        const device = await models.Esp.findByPk(req.params.id);
        if (!device) {
            throw new Error(`Device with id: ${req.params.id} not found`);
        }
        await device.destroy();
        res.status(204).send();
    } catch (error) {
        next(error);
    }
});

export default devices;
